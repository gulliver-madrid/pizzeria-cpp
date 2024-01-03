#include "nivel.h"
#include "controlador_clicks.h"
#include "datos_nivel.h"
#include "estado_nivel.h"
#include "general.h"
#include "vista/enlace_vista.h"
#include "vista/vista.h"
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <memory>
#include <optional>

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = Tiempo::desde_segundos(2.5);
    const auto ESPERA_ENTRE_NIVELES = Tiempo::desde_segundos(2);
} // namespace tiempos

Nivel::Nivel(
    Globales &globales,            //
    const DatosNivel &datos_nivel, //
    const NumNivel &num_nivel,     //
    Grid &grid,                    //
    bool es_el_ultimo              //
)
    : globales(globales), datos_nivel(datos_nivel), num_nivel(num_nivel),
      grid(grid), es_el_ultimo(es_el_ultimo) {
    controlador_clicks = std::shared_ptr<ControladorClicks>();
}

/*
 * Incluye toda la logica para procesar un evento. Devuelve la nueva fase,
 * en caso de que debiera cambiar.
 */
std::optional<FaseNivel> Nivel::procesarEvento(
    sf::Event evento, const BotonesApp &botones, Estado &estado
) {
    auto &ventana = globales.window;
    std::optional<FaseNivel> siguiente_fase;
    switch (evento.type) {
        case sf::Event::Closed:
            ventana.close();
            siguiente_fase = FaseNivel::Saliendo;
            break;
        case sf::Event::Resized:
            {
                // Actualiza la View al nuevo tamano de la ventana
                sf::FloatRect visibleArea(
                    0, 0, evento.size.width, evento.size.height
                );
                ventana.setView(sf::View(visibleArea));
            }
            break;
        case sf::Event::MouseButtonPressed:
            {

                const sf::Vector2i mouse_pos = sf::Mouse::getPosition(ventana);
                const auto comando = controlador_clicks->procesa_click(
                    globales, botones, estado, mouse_pos
                );
                if (!comando) {
                    return std::nullopt;
                }
                assert(modelo_amplio.has_value());
                return modelo_amplio.value().aplica_comando(comando.value());
            }
            break;
        default:
            /* Eventos ignorados */
            break;
    }
    return siguiente_fase;
};

/* Procesa un cambio de fase reciente */
std::optional<AccionGeneral> Nivel::procesa_cambio_de_fase(
    FaseNivel nueva_fase,                   //
    const EnlaceVista &enlace_vista,        //
    Timer &timer_espera_antes_de_resultado, //
    FaseNivel fase_previa,                  //
    GestorTiempoJuego &gestor_tiempo        //
) {
    std::optional<AccionGeneral> posible_accion;
    switch (nueva_fase) {
        case FaseNivel::Activa:
            assert(fase_previa == FaseNivel::MostrandoInstrucciones);
            gestor_tiempo.activar();
            enlace_vista.on_cambio_a_fase_activa();
            break;
        case FaseNivel::EsperaAntesDeResultado:
            assert(fase_previa == FaseNivel::Activa);
            gestor_tiempo.pausar();
            timer_espera_antes_de_resultado.start(
                tiempos::RETARDO_ANTES_DE_RESULTADO
            );
            enlace_vista.on_cambio_a_fase_espera_antes_de_resultado();
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

void mostrar_resultado(
    const Globales &globales,        //
    Estado &estado,                  //
    const EnlaceVista &enlace_vista, //
    Timer &timer_fin_nivel,          //
    sf::Sound &sound                 //
) {
    // Pasa a fase MostrandoResultado
    estado.fase_actual = FaseNivel::MostrandoResultado;
    if (globales.success_buffer) {
        sound.setBuffer(globales.success_buffer.value());
        sound.play();
    }
    timer_fin_nivel.start(tiempos::ESPERA_ENTRE_NIVELES);
    enlace_vista.esconder_paneles();
}

EnlaceVista Nivel::crear_enlace_vista(
    const modelo::ControlPizzas &control_pizzas, //
    std::optional<int> objetivo_estatico         //
) {
    const auto vista_ptr = std::make_shared<Vista>(
        datos_nivel.datos_nivel_para_modelo.es_estatico, //
        globales.font,                                   //
        grid,                                            //
        control_pizzas.get_tipos_disponibles()           //
    );
    vista_ptr->setup(
        datos_nivel.instrucciones, //
        num_nivel,                 //
        objetivo_estatico          //
    );
    return EnlaceVista(vista_ptr);
}

AccionGeneral Nivel::ejecutar() {
    std::optional<int> objetivo_estatico; // Solo se define en estaticos
    modelo_amplio.emplace(ModeloAmplio{datos_nivel});
    assert(modelo_amplio.has_value());
    auto &estado = modelo_amplio.value().estado;
    assert(estado.establecido);
    modelo::ControlPizzas &control_pizzas = estado.estado_modelo.control_pizzas;
    modelo::PizzasAContadores &contadores = control_pizzas.contadores;
    if (datos_nivel.es_estatico().valor) {
        objetivo_estatico = control_pizzas.obtener_objetivo_total_estatico();
    }

    const auto enlace_vista = crear_enlace_vista( //
        control_pizzas, objetivo_estatico
    );

    Timer timer_espera_antes_de_resultado;
    Timer timer_fin_nivel;
    sf::Sound sound;
    assert(!contadores.empty());

    auto &gestor_tiempo = estado.estado_modelo.gestor_tiempo;
    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            auto siguiente_fase =
                procesarEvento(event, enlace_vista.vista->botones, estado);
            // Cambio de fase reciente
            if (!siguiente_fase.has_value()) {
                continue;
            }
            const auto fase_previa = estado.fase_actual;
            estado.fase_actual = siguiente_fase.value();
            const auto accion = procesa_cambio_de_fase(
                estado.fase_actual,              //
                enlace_vista,                    //
                timer_espera_antes_de_resultado, //
                fase_previa,                     //
                gestor_tiempo                    //
            );
            if (accion.has_value()) {
                return accion.value();
            }
        }
        estado.estado_modelo.evaluar_preparacion_pizzas();

        // En funcion de la fase actual (no necesariamente recien iniciada)
        switch (estado.fase_actual) {
            case FaseNivel::EsperaAntesDeResultado:
                if (timer_espera_antes_de_resultado.termino()) {
                    mostrar_resultado(
                        globales, estado, enlace_vista, timer_fin_nivel, sound
                    );
                }
                break;
            case FaseNivel::MostrandoResultado:
                if (!es_el_ultimo && timer_fin_nivel.termino()) {
                    return AccionGeneral::SiguienteNivel;
                };
                break;
        }

        enlace_vista.actualizarIU(globales.window, estado);
        globales.window.display();
    }
    assert(false); // No deberiamos llegar aqui
    return AccionGeneral::Salir;
}
