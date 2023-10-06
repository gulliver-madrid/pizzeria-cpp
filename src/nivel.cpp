#include "nivel.h"
#include "estado_nivel.h"
#include "tiempo.h"
#include "vista/paneles.h"
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
    // std::cout << "procesando evento" << std::endl;
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
/* Procesa el despacho de una pizza de tipo tp, incorporandola al primer pedido
 * disponible y evaluando si ya esta completo.
 * Devuelve un booleano indicando si se sirvió en un pedido (true) o se desechó
 * (false)
 * */
bool procesar_despacho(const TipoPizza tp, Pedidos &pedidos) {
    for (auto &pedido : pedidos) {
        if (pedido.cubierto) {
            continue;
        }
        if (pedido.contenido.count(tp) == 0) {
            continue;
        }
        auto &pedido_tp = pedido.contenido.at(tp);
        if (pedido_tp.servido == pedido_tp.objetivo) {
            continue;
        }
        assert(pedido_tp.servido < pedido_tp.objetivo);
        pedido_tp.servido++;
        pedido.evaluar();
        return true;
    }
    return false;
}

std::optional<FaseNivel> procesar_click_fase_activa(
    const Globales &globales, Botones &botones, Estado &estado,
    const sf::Vector2i mouse_pos
) {

    PizzasAContadores &contadores = estado.control_pizzas.contadores;

    for (auto &par : botones.despachar) {
        auto &tp = par.first;
        auto &boton = par.second;
        auto &contador = contadores.at(tp);
        if (boton.colisiona(mouse_pos, globales)) {
            assert(contador.preparadas > 0);
            contador.preparadas--;
            bool result = procesar_despacho(tp, estado.control_pizzas.pedidos);
            if (result) {
                contador.servidas++;
            }
            break;
        }
    }
    bool faltan = false;
    for (auto &pedido : estado.control_pizzas.pedidos) {
        if (!pedido.cubierto) {
            faltan = true;
            break;
        }
    }
    if (!faltan) {
        return FaseNivel::EsperaAntesDeResultado;
    }

    for (const auto &par : contadores) {
        auto &tp = par.first;
        if (botones.encargar[tp].colisiona(mouse_pos, globales)) {
            auto encargo = EncargoACocina(tp, obtener_tiempo_actual());
            estado.encargos.anadir(encargo);
            return std::nullopt;
        }
    }
    return std::nullopt;
}

/* Procesa un cambio de fase reciente */
void procesa_cambio_de_fase(
    FaseNivel nueva_fase,                   //
    Vista &vista,                           //
    Timer &timer_espera_antes_de_resultado, //
    FaseNivel fase_previa                   //
) {
    vista.procesa_cambio_de_fase(nueva_fase);
    switch (nueva_fase) {
        case FaseNivel::Activa:
            assert(fase_previa == FaseNivel::MostrandoInstrucciones);
            break;
        case FaseNivel::EsperaAntesDeResultado:
            assert(fase_previa == FaseNivel::Activa);
            timer_espera_antes_de_resultado.start(
                tiempos::RETARDO_ANTES_DE_RESULTADO
            );
            break;
    }
}

int obtener_total_preparadas(const PizzasAContadores &contadores) {
    int total_preparadas = 0;
    for (auto &par : contadores) {
        auto contador_tp = par.second;
        total_preparadas += contador_tp.preparadas;
    }
    assert(total_preparadas >= 0);
    return total_preparadas;
}

AccionGeneral nivel(               //
    Globales &globales,            //
    const DatosNivel &datos_nivel, //
    int num_nivel,                 //
    Grid &grid,                    //
    bool es_el_ultimo
) {
    int total_objetivos = -1; // En dinámicos no se usa
    // std::cout << "es estatico? " << datos_nivel.es_estatico << std::endl;
    // std::cout << "Número de nivel: " << num_nivel << std::endl;
    // std::cout << "Número de pedidos en este nivel: "
    //           << datos_nivel.pedidos.size() << std::endl;

    ControlPizzas control_pizzas = {
        datos_nivel.pedidos, datos_nivel.es_estatico};
    Estado estado(FaseNivel::MostrandoInstrucciones, control_pizzas);
    assert(estado.establecido);
    PizzasAContadores &contadores = estado.control_pizzas.contadores;
    // std::cout << "Número de tipos de pizza disponibles: "
    //           << control_pizzas.get_tipos_disponibles().size() << std::endl;
    if (datos_nivel.es_estatico) {
        // Calcular total objetivos
        auto &pedidos = estado.control_pizzas.pedidos;
        assert(pedidos.size() == 1);
        auto &pedido = pedidos[0];
        total_objetivos = 0;
        for (auto &par : pedido.contenido) {
            auto tp = par.first;
            auto pedido_tp = par.second;
            assert(contadores[tp].preparadas == 0);
            total_objetivos += pedido_tp.objetivo;
        }
    }
    Vista vista(globales.font, grid, control_pizzas.get_tipos_disponibles());

    vista.setup(
        datos_nivel.instrucciones, //
        num_nivel,                 //
        datos_nivel.es_estatico,   //
        total_objetivos
    );

    Timer timer_espera_antes_de_resultado;
    Timer timer_fin_nivel;
    sf::Sound sound;

    assert(!contadores.empty());
    // std::cout << "Empezando ciclo de juego en nivel()" << std::endl;
    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            auto nuevo_estado =
                procesarEvento(event, globales, vista.botones, estado);
            // std::cout << "Evento completamente procesado" << std::endl;
            // Cambio de estado reciente
            if (nuevo_estado.has_value()) {
                // std::cout << "Procesando cambio de fase" << std::endl;
                procesa_cambio_de_fase(
                    nuevo_estado.value(), vista,
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
        int total_preparadas = obtener_total_preparadas(contadores);
        if (total_preparadas < MAXIMO_PIZZAS_PREPARADAS) {
            int maximo = MAXIMO_PIZZAS_PREPARADAS - total_preparadas;
            auto tiempo_actual = obtener_tiempo_actual();
            evaluar_preparacion(
                estado.encargos, contadores, maximo, tiempo_actual
            );
        }

        // En función de la fase actual (no necesariamente reciente)
        switch (estado.fase_actual) {
            case FaseNivel::EsperaAntesDeResultado:
                if (timer_espera_antes_de_resultado.termino()) {
                    estado.fase_actual = FaseNivel::MostrandoResultado;
                    if (globales.success_buffer) {
                        sound.setBuffer(globales.success_buffer.value());
                        sound.play();
                    }
                    timer_fin_nivel.start(tiempos::ESPERA_ENTRE_NIVELES);
                    vista.paneles_completos.visible = false;
                }
                break;
            case FaseNivel::MostrandoResultado: {
                if (!es_el_ultimo && timer_fin_nivel.termino()) {
                    return AccionGeneral::SiguienteNivel;
                };
                break;
            }
        }

        vista.actualizarIU(globales.window, estado);
    }
    assert(false); // No deberiamos llegar aqui
    return AccionGeneral::Salir;
}
