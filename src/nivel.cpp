#include "nivel.h"
#include "controlador_clicks.h"
#include "datos_nivel.h"
#include "fase_nivel.h"
#include "log_init.h"
#include "modelo_amplio/aplicador.h"
#include "vista/vista.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <optional>

struct EjecucionEnProceso {
    ModeloAmplio &modelo_amplio;
    EnlaceVista &enlace_vista;
    GestorTiempoJuego &gestor_tiempo_juego;
    Timer &timer_espera_antes_de_resultado;
};

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = sf::seconds(2.5);
    const auto ESPERA_ENTRE_NIVELES = sf::seconds(2);
} // namespace tiempos

namespace {
    /* Procesa un cambio de fase reciente */
    std::optional<AccionGeneral> procesa_cambio_de_fase(
        EjecucionEnProceso &ejecucion, //
        CambioFase cambio_fase         //
    ) {
        const auto fase_previa = cambio_fase.first;
        const auto nueva_fase = cambio_fase.second;
        std::optional<AccionGeneral> posible_accion;
        switch (nueva_fase) {
            case FaseNivel::Activa:
                assert(fase_previa == FaseNivel::MostrandoInstrucciones);
                ejecucion.gestor_tiempo_juego.activar();
                break;
            case FaseNivel::EsperaAntesDeResultado:
                assert(fase_previa == FaseNivel::Activa);
                ejecucion.gestor_tiempo_juego.pausar();
                ejecucion.timer_espera_antes_de_resultado.start(
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
    const Globales &globales,        //
    ModeloAmplio &modelo_amplio,     //
    const EnlaceVista &enlace_vista, //
    Timer &timer_fin_nivel,          //
    sf::Sound &sound                 //
) {
    if (globales.success_buffer) {
        sound.setBuffer(globales.success_buffer.value());
        sound.play();
    }
    timer_fin_nivel.start(tiempos::ESPERA_ENTRE_NIVELES);
    enlace_vista.esconder_paneles();
}

///// Nivel (private) /////

std::optional<FaseNivel> Nivel::_procesa_click(
    const std::shared_ptr<const BotonesApp> &botones,
    const FaseNivel fase_actual //
) {
    auto &ventana = globales.window;
    const sf::Vector2i mouse_pos = sf::Mouse::getPosition(ventana);
    const auto comando = controlador_clicks->procesa_click(
        globales, botones, fase_actual, mouse_pos
    );
    LOG(info) << "Click procesado" << std::endl;
    if (!comando) {
        return std::nullopt;
    }
    assert(modelo_amplio_opcional.has_value());
    LOG(info) << "Antes de aplicar comando" << std::endl;
    auto nueva_fase =
        aplica_comando(modelo_amplio_opcional.value(), comando.value());
    LOG(info) << "Comando aplicado" << std::endl;
    return nueva_fase;
}

EnlaceVista Nivel::_crear_enlace_vista( //
    const modelo::ControlPizzas &control_pizzas
) {
    const auto vista_ptr = std::make_shared<Vista>(
        globales.font,                         //
        grid,                                  //
        control_pizzas.get_tipos_disponibles() //
    );
    EnlaceVista enlace_vista;
    vista_ptr->setup(
        datos_nivel.instrucciones, //
        num_nivel                  //

    );
    enlace_vista.set_vista(vista_ptr);
    return enlace_vista;
}

/*
 * Incluye toda la logica para procesar un evento. Devuelve la nueva fase,
 * en caso de que debiera cambiar.
 */
std::optional<FaseNivel> Nivel::_procesarEvento(
    sf::Event evento,                                 //
    const std::shared_ptr<const BotonesApp> &botones, //
    ModeloAmplio &modelo_amplio                       //
) {
    auto &ventana = globales.window;
    std::optional<FaseNivel> siguiente_fase;
    switch (evento.type) {
        case sf::Event::Closed:
            ventana.close();
            return FaseNivel::Saliendo;
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
            LOG(info) << "Antes de procesar click" << std::endl;
            return _procesa_click(botones, modelo_amplio.get_fase_actual());
        default:
            /* Eventos ignorados */
            LOG(info) << "Evento ignorado" << std::endl;
            LOG(info) << "Tipo de evento: " << evento.type << std::endl;
            break;
    }
    return std::nullopt;
};

/* Procesa un cambio de fase reciente */
std::optional<AccionGeneral> Nivel::_procesa_cambio_de_fase(
    EjecucionEnProceso &ejecucion, FaseNivel nueva_fase
) {
    // Cambio de fase reciente
    const auto fase_previa = ejecucion.modelo_amplio.get_fase_actual();
    CambioFase cambio_fase = {fase_previa, nueva_fase};
    ejecucion.modelo_amplio.set_fase_actual(nueva_fase);
    return procesa_cambio_de_fase(ejecucion, cambio_fase);
}

///// Nivel (public) /////

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

AccionGeneral Nivel::ejecutar() {
    modelo_amplio_opcional.emplace(ModeloAmplio{datos_nivel.datos_modelo_interno
    });
    assert(modelo_amplio_opcional.has_value());
    auto &modelo_amplio = modelo_amplio_opcional.value();
    assert(modelo_amplio.establecido);
    auto &control_pizzas = modelo_amplio.modelo_interno.control_pizzas;
    auto &contadores = control_pizzas.contadores;
    EnlaceVista enlace_vista = _crear_enlace_vista(control_pizzas);
    modelo_amplio.observadores_fase.push_back(enlace_vista);
    modelo_amplio.set_fase_actual(FaseNivel::MostrandoInstrucciones);
    assert(!contadores.empty());
    auto &gestor_tiempo_juego = modelo_amplio.modelo_interno.gestor_tiempo;

    Timer timer_espera_antes_de_resultado;
    Timer timer_fin_nivel;
    EjecucionEnProceso ejecucion_en_proceso = {
        modelo_amplio, enlace_vista, gestor_tiempo_juego,
        timer_espera_antes_de_resultado
    };
    sf::Sound sound;
    sf::Time previo = tiempo::obtener_tiempo_actual();
    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            LOG(info) << "Antes de procesar evento" << std::endl;
            auto siguiente_fase = _procesarEvento( //
                event, enlace_vista.get_botones(), modelo_amplio
            );
            LOG(info) << "Despues de procesar evento" << std::endl;
            if (!siguiente_fase.has_value()) {
                continue;
            }

            const auto accion = _procesa_cambio_de_fase(
                ejecucion_en_proceso, siguiente_fase.value()
            );

            if (accion.has_value()) {
                return accion.value();
            }
        }
        modelo_amplio.modelo_interno.evaluar_preparacion_pizzas();
        const auto fase_previa = modelo_amplio.get_fase_actual();
        // En funcion de la fase actual (no necesariamente recien iniciada)
        switch (modelo_amplio.get_fase_actual()) {
            case FaseNivel::EsperaAntesDeResultado:
                if (timer_espera_antes_de_resultado.termino()) {
                    modelo_amplio.set_fase_actual(FaseNivel::MostrandoResultado
                    );
                }
                break;
            case FaseNivel::MostrandoResultado:
                if (!es_el_ultimo && timer_fin_nivel.termino()) {
                    return AccionGeneral::SiguienteNivel;
                };
                break;
        }
        const auto fase_actual = modelo_amplio.get_fase_actual();
        if (fase_actual != fase_previa &&
            fase_actual == FaseNivel::MostrandoResultado) {
            on_cambio_a_fase_mostrar_resultado(
                globales, modelo_amplio, enlace_vista, timer_fin_nivel, sound
            );
        }
        const auto tiempo_real_actual = tiempo::obtener_tiempo_actual();
        const auto transcurrido = tiempo_real_actual - previo;
        gestor_tiempo_juego.tick(transcurrido);
        previo = tiempo_real_actual;
        enlace_vista.actualizar_interfaz_grafico(
            globales.window, modelo_amplio, tiempo_real_actual
        );
        enlace_vista.dibujar_vista(globales.window);
        globales.window.display();
    }
    assert(false); // No deberiamos llegar aqui
    return AccionGeneral::Salir;
}
