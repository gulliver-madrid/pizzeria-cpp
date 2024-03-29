#include "motor_nivel.h"
#include "controlador_clicks.h"
#include "datos_nivel.h"
#include "fase_nivel.h"
#include "modelo_amplio/aplicador.h"
#include "modelo_amplio/comandos.h"
#include "shared/log_init.h"
#include "shared/num_nivel.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <memory>
#include <optional>

struct EjecucionEnProceso {
    std::optional<ModeloAmplio> &modelo_amplio;
    std::shared_ptr<EnlaceVista> enlace_vista;
    EjecucionEnProceso(
        std::optional<ModeloAmplio> &modelo_amplio_,
        std::shared_ptr<EnlaceVista> enlace_vista_
    )
        : modelo_amplio(modelo_amplio_), enlace_vista(enlace_vista_) {}
};

namespace {

    void update_view_on_window_resize(
        sf::Event::SizeEvent size_event, sf::RenderWindow &ventana
    ) {
        // Actualiza la View al nuevo tamano de la ventana
        sf::FloatRect visibleArea(
            0, 0, static_cast<float>(size_event.width),
            static_cast<float>(size_event.height)
        );
        ventana.setView(sf::View(visibleArea));
    }

    /* Procesa un cambio de fase reciente */
    std::optional<AccionGeneral> impl_procesa_cambio_de_fase(
        EjecucionEnProceso &ejecucion, //
        CambioFase cambio_fase         //
    ) {
        const auto fase_previa = cambio_fase.first;
        const auto nueva_fase = cambio_fase.second;
        std::optional<AccionGeneral> posible_accion;
        switch (nueva_fase) {
            case FaseNivel::Activa:
                assert(fase_previa == FaseNivel::MostrandoInstrucciones);
                ejecucion.modelo_amplio->activar_tiempo_juego();
                break;
            case FaseNivel::EsperaAntesDeResultado:
                assert(fase_previa == FaseNivel::Activa);
                ejecucion.modelo_amplio->iniciar_espera_antes_resultado();
                break;
            case FaseNivel::Reiniciando:
                posible_accion = AccionGeneral::Reiniciar;
                break;
            case FaseNivel::Saliendo:
                posible_accion = AccionGeneral::Salir;
                break;
            default:
                assert(false);
                break;
        }
        return posible_accion;
    }

} // namespace

void on_cambio_a_fase_mostrar_resultado(
    const std::shared_ptr<Globales> globales,  //
    ModeloAmplio &modelo_amplio,               //
    std::shared_ptr<EnlaceVista> enlace_vista, //
    sf::Sound &sound                           //
) {
    if (globales->success_buffer) {
        sound.setBuffer(globales->success_buffer.value());
        sound.play();
    }
    modelo_amplio.iniciar_espera_entre_niveles();
}

///////////////////////////////////////////
// MotorNivel (private)
//////////////////////////////////////////

std::optional<Comando> MotorNivel::_procesa_click(
    const std::shared_ptr<const BotonesApp> botones,
    const FaseNivel fase_actual //
) {
    auto &ventana = globales->window;
    const sf::Vector2i mouse_pos = sf::Mouse::getPosition(ventana);
    const auto comando = controlador_clicks->procesa_click(
        globales, botones, fase_actual, mouse_pos,
        enlace_vista->get_vista()->get_paneles()
    );
    LOG(info) << "Click procesado" << std::endl;
    return comando;
}

std::shared_ptr<EnlaceVista> MotorNivel::_crear_enlace_vista( //
    const modelo::ControlPizzas &control_pizzas
) {
    OptionalFont font;
    assert(!font.exists());
    if (globales) {
        assert(globales->font);
        font.set_pointer(globales->font);
    }
    LOG(info) << "Antes de crear vista";
    const auto vista_ptr = std::make_shared<Vista>();
    LOG(info) << "Vista creada";
    std::string instrucciones;
    if (datos_nivel == nullptr) {
        instrucciones = "No hay instrucciones";
    } else {
        instrucciones = datos_nivel->instrucciones;
    }
    vista_ptr->set_font(font);
    vista_ptr->setup(                           //
        grid,                                   //
        control_pizzas.get_tipos_disponibles(), //
        instrucciones,                          //
        num_nivel                               //
    );
    LOG(info) << "Vista inicializada";
    auto enlace_vista_ = std::make_shared<EnlaceVista>();
    enlace_vista_->set_vista(vista_ptr);
    return enlace_vista_;
}

/*
 * Incluye toda la logica para procesar un evento. Devuelve la nueva fase,
 * en caso de que debiera cambiar.
 */
std::optional<AccionGeneral> MotorNivel::_procesar_evento(
    sf::Event evento, //
    const std::shared_ptr<const BotonesApp> botones
) {
    auto &ventana = globales->window;
    std::optional<Comando> comando;
    switch (evento.type) {
        case sf::Event::Closed:
            comando = Comando::Salir{};
            break;
        case sf::Event::Resized:
            update_view_on_window_resize(evento.size, ventana);
            break;
        case sf::Event::MouseButtonPressed:
            LOG(info) << "Antes de procesar click" << std::endl;
            comando = _procesa_click(botones, modelo_amplio->get_fase_actual());
        default:
            /* Eventos ignorados */
            LOG(info) << "Evento ignorado";
            LOG(info) << "Tipo de evento: " << evento.type;
            break;
    }
    if (!comando) {
        return std::nullopt;
    }
    assert(modelo_amplio);
    LOG(info) << "Antes de aplicar comando";
    return aplica_comando(comando.value());
};

/* Procesa un cambio de fase reciente */
std::optional<AccionGeneral>
MotorNivel::_procesa_cambio_de_fase(FaseNivel nueva_fase) {
    // Cambio de fase reciente
    const auto fase_previa = modelo_amplio->get_fase_actual();
    CambioFase cambio_fase = {fase_previa, nueva_fase};
    establecer_fase(nueva_fase);
    assert(ejecucion_en_proceso);
    return impl_procesa_cambio_de_fase(*ejecucion_en_proceso, cambio_fase);
}

void MotorNivel::establecer_fase(FaseNivel nueva_fase) {
    modelo_amplio->set_fase_actual(nueva_fase);
}

std::shared_ptr<VistaObservable> MotorNivel::get_vista() const { //
    return enlace_vista->get_vista();
}

///////////////////////////////////////////
// MotorNivel (public)
//////////////////////////////////////////

MotorNivel::MotorNivel(
    std::shared_ptr<Globales> globales,      //
    std::shared_ptr<DatosNivel> datos_nivel, //
    const NumNivelOpcional num_nivel,        //
    std::shared_ptr<Grid> grid               //
)
    : globales(globales), datos_nivel(datos_nivel), num_nivel(num_nivel),
      grid(grid) {

    controlador_clicks = std::shared_ptr<ControladorClicks>();

    LOG(info) << "Creando nivel " << to_string(num_nivel) << std::endl;
    if (datos_nivel) {
        modelo_amplio.emplace(datos_nivel->datos_modelo_interno);
    } else {
        modelo_amplio.emplace();
    };
    assert(modelo_amplio);
    LOG(info) << "modelo amplio creado";
    assert(modelo_amplio->establecido);
    LOG(info) << "modelo amplio establecido";
    auto &control_pizzas = modelo_amplio->modelo_interno.control_pizzas;
    LOG(info) << "control piezas disponible para enlace_vista";
    enlace_vista = _crear_enlace_vista(control_pizzas);
    LOG(info) << "enlace_vista creado";
    modelo_amplio->observadores_fase.push_back(enlace_vista);
}

// Inicializa elementos antes de la ejecucion
void MotorNivel::setup() {
    using Tipo = TipoGestorTiempo;
    assert(modelo_amplio);

    ejecucion_en_proceso =
        std::make_shared<EjecucionEnProceso>(modelo_amplio, enlace_vista);
    auto &gtg = modelo_amplio->gestor_tiempo_general;

    gtg.anade_gestor(
        Tipo::timer_antes_resultado, std::make_shared<GestorTimer>()
    );

    gtg.anade_gestor(Tipo::timer_fin_nivel, std::make_shared<GestorTimer>());

    auto gestor_tiempo_real = std::make_shared<GestorTiempoControlable>();
    gtg.anade_gestor(Tipo::gestor_tiempo_real, gestor_tiempo_real);
    gestor_tiempo_real->activar();

    gtg.anade_gestor(
        Tipo::gestor_tiempo_juego,
        modelo_amplio->modelo_interno.gestor_tiempo_juego
    );
}

std::optional<AccionGeneral> MotorNivel::aplica_comando(const Comando &comando
) {
    std::optional<AccionGeneral> accion;
    auto result = aplica_comando_a_modelo(modelo_amplio.value(), comando);
    if (result.has_value()) {
        accion = _procesa_cambio_de_fase(result.value());
    };
    return accion;
}

std::optional<AccionGeneral> MotorNivel::procesar_evento(sf::Event event) {
    LOG(info) << "Antes de procesar evento";
    auto accion = _procesar_evento( //
        event, enlace_vista->get_botones()
    );
    LOG(info) << "Despues de procesar evento";
    return accion;
}

/* Procesamiento de cada ciclo tras procesar los eventos */
std::optional<AccionGeneral> MotorNivel::procesar_ciclo() {
    assert(modelo_amplio);
    modelo_amplio->modelo_interno.evaluar_preparacion_pizzas();
    const auto fase_previa = modelo_amplio->get_fase_actual();

    // En funcion de la fase actual (no necesariamente recien iniciada)
    switch (modelo_amplio->get_fase_actual()) {
        case FaseNivel::EsperaAntesDeResultado:
            if (modelo_amplio->termino_timer(
                    TipoGestorTiempo::timer_antes_resultado
                )) {
                LOG(info) << "Se debe mostrar el resultado";
                establecer_fase(FaseNivel::MostrandoResultado);
            }
            break;
        case FaseNivel::MostrandoResultado:
            if (modelo_amplio->termino_timer( //
                    TipoGestorTiempo::timer_fin_nivel
                )) {
                LOG(info) << "Se debe pasar al siguiente nivel";
                return AccionGeneral::SiguienteNivel;
            };
            break;
    }
    const auto fase_actual = modelo_amplio->get_fase_actual();
    if (fase_actual != fase_previa &&
        fase_actual == FaseNivel::MostrandoResultado) {
        on_cambio_a_fase_mostrar_resultado(
            globales, modelo_amplio.value(), enlace_vista, sound
        );
    }
    return std::nullopt;
}

void MotorNivel::actualizar_interfaz_grafico() {
    enlace_vista->actualizar_interfaz_grafico(modelo_amplio.value());
}

void MotorNivel::tick(sf::Time transcurrido) {
    assert(modelo_amplio);
    modelo_amplio.value().gestor_tiempo_general.tick(transcurrido);
}
