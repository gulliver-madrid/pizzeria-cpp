#include "nivel.h"
#include "actualizar_iu.h"
#include "tiempo.h"
#include "vista/vista.h"
#include "vista/vista_data.h"
#include <SFML/Window.hpp>
#include <cassert>

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
            return Reiniciando;
        }
        // Dependientes del estado
        if (estado.fase_actual == MostrandoInstrucciones) {
            auto bounds = botones.empezar.boton.getGlobalBounds();
            if (botones.empezar.colisiona(mousePos, globales)) {
                return Activa;
            }
        } else if (estado.fase_actual == Activa) {
            for (auto &par : botones.despachar) {
                auto &boton = par.second;
                auto &contador = estado.contadores[par.first];
                if (boton.colisiona(mousePos, globales) &&
                    contador.preparadas > 0) {
                    contador.preparadas--;
                    contador.servidas++;
                    break;
                }
            }
            bool faltan = false;
            for (auto tp : tipos_de_pizza) {
                if (estado.contadores[tp].servidas <
                    estado.contadores[tp].objetivo) {
                    faltan = true;
                    break;
                }
            }
            if (!faltan) {
                return EsperaAntesDeResultado;
            }
            for (const auto &tp : tipos_de_pizza) {
                if (botones.encargar[tp].colisiona(mousePos, globales)) {
                    EncargoACocina encargo =
                        crear_encargo(tp, obtener_tiempo_actual());
                    estado.encargadas.push_back(encargo);
                    break;
                }
            }
        }
    }
    return std::nullopt;
};

/* Procesa un cambio de fase reciente */
void procesa_cambio_de_fase(
    FaseNivel nueva_fase,                   //
    Botones &botones,                       //
    PanelesCompletos &paneles_completos,    //
    Timer &timer_espera_antes_de_resultado, //
    FaseNivel fase_previa                   //
) {
    switch (nueva_fase) {
        case Activa:
            assert(fase_previa == MostrandoInstrucciones);
            botones.empezar.visible = false;
            botones.mostrar_botones_nivel(true);
            paneles_completos.visible = true;
            break;
        case EsperaAntesDeResultado:
            assert(fase_previa == Activa);
            botones.mostrar_botones_nivel(false);
            timer_espera_antes_de_resultado.start(
                tiempos::RETARDO_ANTES_DE_RESULTADO
            );
            break;
    }
}

AccionGeneral nivel(         //
    Globales &globales,      //
    Estado &estado,          //
    DatosNivel &datos_nivel, //
    Grid &grid,              //
    bool es_el_ultimo
) {
    // Iniciamos el estado
    estado.fase_actual = MostrandoInstrucciones;
    for (auto tp : tipos_de_pizza) {
        estado.contadores[tp].preparadas =
            datos_nivel.pedidos.pizzas[tp].pizzas_preparadas_iniciales;
        estado.contadores[tp].objetivo =
            datos_nivel.pedidos.pizzas[tp].objetivo_pizzas;
    }
    int total = 0;
    for (auto tp : tipos_de_pizza) {
        total += estado.contadores[tp].objetivo;
    }
    auto instrucciones = generar_etiqueta_instrucciones(
        globales.font, datos_nivel.instrucciones, total
    );
    auto resultado = generar_etiqueta_resultado(globales.font);

    EtiquetasInfo etiquetas_info = {instrucciones, resultado};

    PanelesCompletos paneles_completos(globales.font);
    EtiquetasContadores etiquetas_contadores;
    etiquetas_contadores.setup(globales.font);

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
                estado.encargadas, estado.contadores, maximo, tiempo_actual
            );
        }

        // En función del estado (no necesariamente reciente)
        switch (estado.fase_actual) {
            case EsperaAntesDeResultado:
                if (timer_espera_antes_de_resultado.termino()) {
                    estado.fase_actual = MostrandoResultado;
                    if (globales.success_buffer) {
                        sound.setBuffer(globales.success_buffer.value());
                        sound.play();
                    }
                    timer_fin_nivel.start(tiempos::ESPERA_ENTRE_NIVELES);
                    paneles_completos.visible = false;
                }
                break;
            case MostrandoResultado: {
                if (!es_el_ultimo && timer_fin_nivel.termino()) {
                    return AccionGeneral::SiguienteNivel;
                };
                break;
            }
        }

        actualizarIU(
            globales.window, botones, paneles_completos, etiquetas_contadores,
            etiquetas_info, estado, grid, globales.font
        );
    }
    assert(false); // No deberiamos llegar aqui
    return AccionGeneral::Salir;
}
