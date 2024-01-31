#include "nivel.h"
#include "controlador_clicks.h"
#include "datos_nivel.h"
#include "fase_nivel.h"
#include "modelo_amplio/aplicador.h"
#include "shared/log_init.h"
#include "shared/num_nivel.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <optional>

struct EjecucionEnProceso {
    std::optional<ModeloAmplio> &modelo_amplio;
    std::shared_ptr<EnlaceVista> enlace_vista;
    std::shared_ptr<GestorTiempoJuego> gestor_tiempo_juego;
    std::shared_ptr<GestorTimer> timer_espera_antes_de_resultado;
    EjecucionEnProceso(
        std::optional<ModeloAmplio> &modelo_amplio_,
        std::shared_ptr<EnlaceVista> enlace_vista_,
        std::shared_ptr<GestorTiempoJuego> gestor_tiempo_juego_,
        std::shared_ptr<GestorTimer> timer_espera_antes_de_resultado_
    )
        : modelo_amplio(modelo_amplio_), enlace_vista(enlace_vista_),
          gestor_tiempo_juego(gestor_tiempo_juego_),
          timer_espera_antes_de_resultado(timer_espera_antes_de_resultado_) {}
};

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = sf::seconds(2.5);
    const auto ESPERA_ENTRE_NIVELES = sf::seconds(3);
} // namespace tiempos

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
                ejecucion.gestor_tiempo_juego->activar();
                break;
            case FaseNivel::EsperaAntesDeResultado:
                assert(fase_previa == FaseNivel::Activa);
                ejecucion.gestor_tiempo_juego->pausar();
                ejecucion.timer_espera_antes_de_resultado->start(
                    tiempos::RETARDO_ANTES_DE_RESULTADO
                );
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
    const std::shared_ptr<Globales> globales,     //
    const ModeloAmplio &modelo_amplio,            //
    std::shared_ptr<EnlaceVista> enlace_vista,    //
    std::shared_ptr<GestorTimer> timer_fin_nivel, //
    sf::Sound &sound                              //
) {
    if (globales->success_buffer) {
        sound.setBuffer(globales->success_buffer.value());
        sound.play();
    }
    timer_fin_nivel->start(tiempos::ESPERA_ENTRE_NIVELES);
    enlace_vista->esconder_paneles();
}

///////////////////////////////////////////
// Nivel (private)
//////////////////////////////////////////

std::optional<FaseNivel> Nivel::_procesa_click(
    const std::shared_ptr<const BotonesApp> botones,
    const FaseNivel fase_actual //
) {
    auto &ventana = globales->window;
    const sf::Vector2i mouse_pos = sf::Mouse::getPosition(ventana);
    const auto comando = controlador_clicks->procesa_click(
        globales, botones, fase_actual, mouse_pos
    );
    LOG(info) << "Click procesado" << std::endl;
    if (!comando) {
        return std::nullopt;
    }
    assert(modelo_amplio);
    LOG(info) << "Antes de aplicar comando" << std::endl;
    auto nueva_fase = aplica_comando(*modelo_amplio, comando.value());
    LOG(info) << "Comando aplicado" << std::endl;
    return nueva_fase;
}

std::shared_ptr<EnlaceVista> Nivel::_crear_enlace_vista( //
    const modelo::ControlPizzas &control_pizzas
) {
    OptionalFont font;
    assert(!font.exists());
    if (globales) {
        assert(globales->font);
        font.set_pointer(globales->font);
    }
    LOG(info) << "Creando vista" << std::endl;
    const auto vista_ptr = std::make_shared<Vista>();
    LOG(info) << "Vista creada" << std::endl;
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
    LOG(info) << "Vista inicializada" << std::endl;
    auto enlace_vista_ = std::make_shared<EnlaceVista>();
    enlace_vista_->set_vista(vista_ptr);
    return enlace_vista_;
}

/*
 * Incluye toda la logica para procesar un evento. Devuelve la nueva fase,
 * en caso de que debiera cambiar.
 */
std::optional<FaseNivel> Nivel::_procesarEvento(
    sf::Event evento, //
    const std::shared_ptr<const BotonesApp> botones

) {
    auto &ventana = globales->window;
    std::optional<FaseNivel> siguiente_fase;
    switch (evento.type) {
        case sf::Event::Closed:
            return FaseNivel::Saliendo;
        case sf::Event::Resized:
            update_view_on_window_resize(evento.size, ventana);
            break;
        case sf::Event::MouseButtonPressed:
            LOG(info) << "Antes de procesar click" << std::endl;
            return _procesa_click(botones, modelo_amplio->get_fase_actual());
        default:
            /* Eventos ignorados */
            LOG(info) << "Evento ignorado" << std::endl;
            LOG(info) << "Tipo de evento: " << evento.type << std::endl;
            break;
    }
    return std::nullopt;
};

///////////////////////////////////////////
// Nivel (public)
//////////////////////////////////////////

Nivel::Nivel(
    std::shared_ptr<Globales> globales,      //
    std::shared_ptr<DatosNivel> datos_nivel, //
    const NumNivelOpcional num_nivel,        //
    std::shared_ptr<Grid> grid               //
)
    : globales(globales), datos_nivel(datos_nivel), num_nivel(num_nivel),
      grid(grid) {

    controlador_clicks = std::shared_ptr<ControladorClicks>();

    LOG(info) << "Creando nivel " << num_nivel.to_string() << std::endl;
    if (datos_nivel) {
        modelo_amplio.emplace(datos_nivel->datos_modelo_interno);
    } else {
        modelo_amplio.emplace();
    };
    assert(modelo_amplio);
    LOG(info) << "modelo amplio creado" << std::endl;
    assert(modelo_amplio->establecido);
    LOG(info) << "modelo amplio establecido" << std::endl;
    auto &control_pizzas = modelo_amplio->modelo_interno.control_pizzas;
    LOG(info) << "tenemos control piezas" << std::endl;
    enlace_vista = _crear_enlace_vista(control_pizzas);
    LOG(info) << "enlace_vista creado" << std::endl;
    modelo_amplio->observadores_fase.push_back(enlace_vista);
}

// Inicializa elementos antes de la ejecucion
void Nivel::setup() {
    auto &gestor_tiempo_juego = modelo_amplio->modelo_interno.gestor_tiempo;
    timer_espera_antes_de_resultado = std::make_shared<GestorTimer>();
    assert(timer_espera_antes_de_resultado);
    ejecucion_en_proceso = std::make_shared<EjecucionEnProceso>(
        modelo_amplio, enlace_vista, gestor_tiempo_juego,
        timer_espera_antes_de_resultado
    );
    gestor_tiempo_general.gestores["timer_espera_antes_de_resultado"] =
        timer_espera_antes_de_resultado;
    gestor_tiempo_general.gestores["timer_fin_nivel"] =
        std::make_shared<GestorTimer>();
    gestor_tiempo_general.gestores["gestor_tiempo_juego"] =
        ejecucion_en_proceso->gestor_tiempo_juego;
}

AccionGeneral Nivel::ejecutar() {
    auto &control_pizzas = modelo_amplio->modelo_interno.control_pizzas;
    auto &contadores = control_pizzas.contadores;
    establecer_fase(FaseNivel::MostrandoInstrucciones);
    assert(!contadores.empty());
    LOG(info) << "modelo amplio iniciado" << std::endl;

    setup();

    std::optional<AccionGeneral> accion;
    sf::Time previo = tiempo::obtener_tiempo_actual();
    LOG(info) << "Empezando bucle de juego";
    while (globales->window.isOpen()) {
        LOG(info) << "Nueva iteracion del bucle de juego";
        sf::Event event;
        while (globales->window.pollEvent(event)) {
            accion = procesar_evento(event);
            if (accion.has_value()) {
                return accion.value();
            }
        }

        accion = procesar_ciclo();
        if (accion.has_value()) {
            break;
        }

        const auto tiempo_real_actual = tiempo::obtener_tiempo_actual();
        const auto transcurrido = tiempo_real_actual - previo;

        gestor_tiempo_general.tick(transcurrido);
        actualizar_interfaz_grafico(tiempo_real_actual);

        previo = tiempo_real_actual;
        enlace_vista->dibujar_vista(globales->window);
        globales->window.display();
    }
    assert(accion.has_value());
    return accion.value();
}

std::optional<AccionGeneral> Nivel::procesar_evento(sf::Event event) {
    LOG(info) << "Antes de procesar evento";
    auto siguiente_fase = _procesarEvento( //
        event, enlace_vista->get_botones()
    );
    LOG(info) << "Despues de procesar evento";
    if (!siguiente_fase.has_value()) {
        return std::nullopt;
    }

    return procesa_cambio_de_fase(siguiente_fase.value());
}

std::optional<AccionGeneral> Nivel::procesar_ciclo() {
    modelo_amplio->modelo_interno.evaluar_preparacion_pizzas();
    const auto fase_previa = modelo_amplio->get_fase_actual();

    auto timer_fin_nivel_ = gestor_tiempo_general.gestores["timer_fin_nivel"];
    auto timer_fin_nivel =
        std::dynamic_pointer_cast<GestorTimer>(timer_fin_nivel_);
    assert(timer_fin_nivel);

    // En funcion de la fase actual (no necesariamente recien iniciada)
    switch (modelo_amplio->get_fase_actual()) {
        case FaseNivel::EsperaAntesDeResultado:
            if (timer_espera_antes_de_resultado->termino()) {
                LOG(info) << "Se debe mostrar el resultado";
                establecer_fase(FaseNivel::MostrandoResultado);
            }
            break;
        case FaseNivel::MostrandoResultado:
            {
                if (timer_fin_nivel->termino()) {
                    LOG(info) << "Se debe pasar al siguiente nivel";
                    return AccionGeneral::SiguienteNivel;
                };
            }
            break;
    }
    const auto fase_actual = modelo_amplio->get_fase_actual();
    if (fase_actual != fase_previa &&
        fase_actual == FaseNivel::MostrandoResultado) {
        on_cambio_a_fase_mostrar_resultado(
            globales, modelo_amplio.value(), enlace_vista, timer_fin_nivel,
            sound
        );
    }
    return std::nullopt;
}

void Nivel::actualizar_interfaz_grafico(const sf::Time tiempo_real_actual) {
    enlace_vista->actualizar_interfaz_grafico(
        modelo_amplio.value(), tiempo_real_actual
    );
}

/* Procesa un cambio de fase reciente */
std::optional<AccionGeneral> Nivel::procesa_cambio_de_fase(FaseNivel nueva_fase
) {
    // Cambio de fase reciente
    const auto fase_previa = modelo_amplio->get_fase_actual();
    CambioFase cambio_fase = {fase_previa, nueva_fase};
    establecer_fase(nueva_fase);
    assert(ejecucion_en_proceso);
    return impl_procesa_cambio_de_fase(*ejecucion_en_proceso, cambio_fase);
}

void Nivel::establecer_fase(FaseNivel nueva_fase) {
    modelo_amplio->set_fase_actual(nueva_fase);
}

std::shared_ptr<VistaObservable> Nivel::get_vista() const { //
    return enlace_vista->get_vista();
}
