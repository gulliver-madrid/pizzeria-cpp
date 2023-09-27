#include "nivel.h"
#include "actualizar_iu.h"
#include "tiempo.h"
#include "vista/vista.h"
#include "vista/vista_data.h"
#include <SFML/Window.hpp>
#include <cassert>

/* Procesa un click realizado durante la fase activa.
 * Devuelve la nueva fase, en caso de que debiera cambiar
 */
std::optional<FaseNivel> procesar_click_fase_activa(
    const Globales &globales, Botones &botones, Estado &estado,
    const sf::Vector2i mouse_pos
);

// Incluye toda la lógica para procesar un evento
std::optional<FaseNivel> procesarEvento(
    sf::Event evento, Globales &globales, Botones &botones, Estado &estado
) {
    auto &ventana = globales.window;
    // Cierre de ventana
    if (evento.type == sf::Event::Closed) {
        ventana.close();
        return FaseNivel::Saliendo;
    }

    else if (evento.type == sf::Event::Resized) {
        // Actualiza la View al nuevo tamaño de la ventana
        sf::FloatRect visibleArea(0, 0, evento.size.width, evento.size.height);
        ventana.setView(sf::View(visibleArea));
    }

    // Pulsación botón
    else if (evento.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);

        // Fijos
        if (botones.salir.colisiona(mousePos, globales)) {
            ventana.close();
            return FaseNivel::Saliendo;
        } else if (botones.reiniciar.colisiona(mousePos, globales)) {
            return FaseNivel::Reiniciando;
        }
        // Dependientes del estado
        if (estado.fase_actual == FaseNivel::MostrandoInstrucciones) {
            auto bounds = botones.empezar.boton.getGlobalBounds();
            if (botones.empezar.colisiona(mousePos, globales)) {
                return FaseNivel::Activa;
            }
        } else if (estado.fase_actual == FaseNivel::Activa) {
            auto nueva_fase =
                procesar_click_fase_activa(globales, botones, estado, mousePos);
            if (nueva_fase.has_value()) {
                return nueva_fase;
            }
        }
    }
    return std::nullopt;
};

std::optional<FaseNivel> procesar_click_fase_activa(
    const Globales &globales, Botones &botones, Estado &estado,
    const sf::Vector2i mouse_pos
) {
    for (auto &par : botones.despachar) {
        auto &boton = par.second;
        auto &contador = estado.contadores[par.first];
        if (boton.colisiona(mouse_pos, globales)) {
            assert(contador.preparadas > 0);
            contador.preparadas--;
            contador.servidas++;
            return std::nullopt;
        }
    }
    bool faltan = false;
    for (auto tp : tipos_de_pizza) {
        if (estado.contadores[tp].servidas < estado.contadores[tp].objetivo) {
            faltan = true;
            break;
        }
    }
    if (!faltan) {
        return FaseNivel::EsperaAntesDeResultado;
    }
    for (const auto &tp : tipos_de_pizza) {
        if (botones.encargar[tp].colisiona(mouse_pos, globales)) {
            EncargoACocina encargo = crear_encargo(tp, obtener_tiempo_actual());
            estado.encargos.datos.push_back(encargo);
            return std::nullopt;
        }
    }
    return std::nullopt;
}

/* Procesa un cambio de fase reciente */
void procesa_cambio_de_fase(
    FaseNivel nueva_fase,                   //
    Botones &botones,                       //
    PanelesCompletos &paneles_completos,    //
    Timer &timer_espera_antes_de_resultado, //
    FaseNivel fase_previa                   //
) {
    switch (nueva_fase) {
        case FaseNivel::Activa:
            assert(fase_previa == FaseNivel::MostrandoInstrucciones);
            botones.empezar.visible = false;
            botones.mostrar_botones_nivel(true);
            paneles_completos.visible = true;
            break;
        case FaseNivel::EsperaAntesDeResultado:
            assert(fase_previa == FaseNivel::Activa);
            botones.mostrar_botones_nivel(false);
            timer_espera_antes_de_resultado.start(
                tiempos::RETARDO_ANTES_DE_RESULTADO
            );
            break;
    }
}

AccionGeneral nivel(               //
    Globales &globales,            //
    Estado &estado,                //
    const DatosNivel &datos_nivel, //
    Grid &grid,                    //
    bool es_el_ultimo
) {
    // Iniciamos el estado
    estado.fase_actual = FaseNivel::MostrandoInstrucciones;
    for (auto tp : tipos_de_pizza) {
        estado.contadores[tp].preparadas =
            datos_nivel.pedidos.pizzas.at(tp).pizzas_preparadas_iniciales;
        estado.contadores[tp].objetivo =
            datos_nivel.pedidos.pizzas.at(tp).objetivo_pizzas;
    }
    int total_objetivos = 0;
    for (auto tp : tipos_de_pizza) {
        total_objetivos += estado.contadores[tp].objetivo;
    }

    EtiquetasGenerales etiquetas;
    etiquetas.setup(globales, datos_nivel, total_objetivos);

    PanelesCompletos paneles_completos(globales.font);

    // Botones
    Botones botones(globales.font);

    // Mostrar botones iniciales
    botones.reiniciar.visible = true;
    botones.salir.visible = true;
    botones.empezar.visible = true;

    Timer timer_espera_antes_de_resultado;
    Timer timer_fin_nivel;
    sf::Sound sound;
    int frame = 0;

    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            auto nuevo_estado =
                procesarEvento(event, globales, botones, estado);
            // Cambio de estado reciente
            if (nuevo_estado.has_value()) {
                procesa_cambio_de_fase(
                    nuevo_estado.value(), botones, paneles_completos,
                    timer_espera_antes_de_resultado, estado.fase_actual
                );
                estado.fase_actual = nuevo_estado.value();
                if (estado.fase_actual == FaseNivel::Reiniciando) {
                    return AccionGeneral::Reiniciar;
                } else if (estado.fase_actual == FaseNivel::Saliendo) {
                    return AccionGeneral::Salir;
                }
            }
        }

        int total_preparadas = 0;
        for (auto tp : tipos_de_pizza) {
            total_preparadas += estado.contadores[tp].preparadas;
        }

        if (total_preparadas < MAXIMO_PIZZAS_PREPARADAS) {
            int maximo = MAXIMO_PIZZAS_PREPARADAS - total_preparadas;
            auto tiempo_actual = obtener_tiempo_actual();
            evaluar_preparacion(
                estado.encargos, estado.contadores, maximo, tiempo_actual
            );
        }

        // En función del estado (no necesariamente reciente)
        switch (estado.fase_actual) {
            case FaseNivel::EsperaAntesDeResultado:
                if (timer_espera_antes_de_resultado.termino()) {
                    estado.fase_actual = FaseNivel::MostrandoResultado;
                    if (globales.success_buffer) {
                        sound.setBuffer(globales.success_buffer.value());
                        sound.play();
                    }
                    timer_fin_nivel.start(tiempos::ESPERA_ENTRE_NIVELES);
                    paneles_completos.visible = false;
                }
                break;
            case FaseNivel::MostrandoResultado: {
                if (!es_el_ultimo && timer_fin_nivel.termino()) {
                    return AccionGeneral::SiguienteNivel;
                };
                break;
            }
        }

        actualizarIU(
            globales.window, botones, paneles_completos, etiquetas, estado,
            grid, globales.font
        );
    }
    assert(false); // No deberiamos llegar aqui
    return AccionGeneral::Salir;
}
