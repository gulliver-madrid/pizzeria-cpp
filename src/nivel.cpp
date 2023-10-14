#include "nivel.h"
#include "estado_nivel.h"
#include "tiempo.h"
#include "vista/paneles.h"
#include "vista/vista.h"
#include "vista/vista_data.h"
#include <SFML/Window.hpp>
#include <cassert>

Nivel::Nivel(
    Globales &globales,            //
    const DatosNivel &datos_nivel, //
    NumNivel num_nivel,            //
    Grid &grid,                    //
    bool es_el_ultimo              //
)
    : globales(globales), datos_nivel(datos_nivel), num_nivel(num_nivel),
      grid(grid), es_el_ultimo(es_el_ultimo) {}

/*
 * Incluye toda la lógica para procesar un evento. Devuelve la nueva fase, en
 * caso de que debiera cambiar.
 */
std::optional<FaseNivel> Nivel::procesarEvento(
    sf::Event evento, const Botones &botones, Estado &estado
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
        const sf::Vector2i mouse_pos = sf::Mouse::getPosition(ventana);
        const auto pulsado = [this, &mouse_pos](const BotonConTexto &boton) {
            return this->globales.detecta_colision(boton, mouse_pos);
        };

        // Fijos
        if (pulsado(botones.generales.salir)) {
            ventana.close();
            return FaseNivel::Saliendo;
        } else if (pulsado(botones.generales.reiniciar)) {
            return FaseNivel::Reiniciando;
        } else if (pulsado(botones.generales.alternar_grid)) {
            assert(MODO_DESARROLLO);
            estado.mostrando_grid = !estado.mostrando_grid;
        }
        // Dependientes del estado
        if (estado.fase_actual == FaseNivel::MostrandoInstrucciones) {
            if (pulsado(botones.empezar)) {
                return FaseNivel::Activa;
            }
        } else if (estado.fase_actual == FaseNivel::Activa) {
            const auto tipos_pizza_disponibles =
                estado.control_pizzas.get_tipos_disponibles();
            bool despacho = false;
            for (const auto &tp : tipos_pizza_disponibles) {
                if (pulsado(botones.encargar.at(tp))) {
                    auto encargo = EncargoACocina(tp, obtener_tiempo_actual());
                    estado.encargos.anadir(encargo);
                    return std::nullopt;
                }
                if (pulsado(botones.despachar.at(tp))) {
                    estado.control_pizzas.procesar_despacho(tp);
                    despacho = true;
                    break;
                }
            }
            if (despacho &&
                !estado.control_pizzas.faltan_pedidos_por_cubrir()) {
                return FaseNivel::EsperaAntesDeResultado;
            }
        }
    }
    return std::nullopt;
};

/* Procesa un cambio de fase reciente */
void Nivel::procesa_cambio_de_fase(
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

AccionGeneral Nivel::ejecutar() {
    int total_objetivos = -1; // En dinámicos no se usa
    // std::cout << "es estatico? " << datos_nivel.es_estatico << std::endl;
    // std::cout << "Número de nivel: " << num_nivel << std::endl;
    // std::cout << "Número de pedidos en este nivel: "
    //           << datos_nivel.pedidos.size() << std::endl;

    ControlPizzas control_pizzas = {
        datos_nivel.pedidos, datos_nivel.es_estatico};
    Estado estado(FaseNivel::MostrandoInstrucciones, control_pizzas);
    assert(estado.establecido);
    PizzasAContadores &contadores = control_pizzas.contadores;
    // std::cout << "Número de tipos de pizza disponibles: "
    //           << control_pizzas.get_tipos_disponibles().size() << std::endl;
    if (datos_nivel.es_estatico) {
        // Calcular total objetivos
        auto &pedidos = control_pizzas.pedidos;
        assert(pedidos.size() == 1);
        auto &pedido = pedidos[0];
        total_objetivos = control_pizzas.obtener_total_objetivos(pedido);
    }
    Vista vista(
        datos_nivel.es_estatico,               //
        globales.font,                         //
        grid,                                  //
        control_pizzas.get_tipos_disponibles() //
    );

    vista.setup(
        datos_nivel.instrucciones, //
        num_nivel,                 //
        total_objetivos            //
    );

    Timer timer_espera_antes_de_resultado;
    Timer timer_fin_nivel;
    sf::Sound sound;

    assert(!contadores.empty());
    // std::cout << "Empezando ciclo de juego en nivel()" << std::endl;
    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            auto nuevo_estado = procesarEvento(event, vista.botones, estado);
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
        int total_preparadas = estado.control_pizzas.obtener_total_preparadas();
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
