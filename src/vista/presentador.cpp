#include "presentador.h"
#include "../modelo/dominio.h"
#include "../templates/helpers.h"
#include "../tiempo.h"
#include "cadenas.h"
#include "vista_shared.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

namespace presentador {

    namespace impl {
        std::string crea_linea_completitud_pizza(
            const dominio::TipoPizza tp, UInt parte, UInt todo
        ) {
            assert(has_key(tipo_pizza_to_string, tp));
            const auto nombre_pizza = tipo_pizza_to_string.at(tp);
            std::string s = (         //
                nombre_pizza + ": " + //
                parte.to_string() +   //
                std::string("/") +    //
                todo.to_string()      //
            );
            return s;
        }

        /* Crea una string representando un pedido. Una linea por tipo de pizza,
         * con el formato TipoPizza: actual/objetivo
         */
        std::string pedido_to_string(const Pedido &pedido) {
            std::string s;
            size_t ultimo = pedido.contenido.size() - 1;
            size_t i = 0;
            for (auto &[tp, pedido_tp] : pedido.contenido) {
                s.append(
                    crea_linea_completitud_pizza(
                        tp, pedido_tp.servido, pedido_tp.objetivo
                    ) +
                    ((i < ultimo) ? "\n" : "")
                );
                i++;
            }
            return s;
        }
        /* Crea una vista representando un pedido, que incluye una cadena y el
         * numero de items.
         */
        std::pair<std::string, size_t> pedido_to_vista(const Pedido &pedido) {
            std::string s = pedido_to_string(pedido);
            const size_t num_items = pedido.contenido.size();
            return std::make_pair(s, num_items);
        }
    } // namespace impl

    PresentacionPedidos
    crear_presentacion_pedidos(const modelo::Pedidos &pedidos //
    ) {
        // Creamos las tarjetas de los pedidos
        PresentacionPedidos presentacion_pedidos;
        for (auto &pedido : pedidos) {
            presentacion_pedidos.emplace_back(impl::pedido_to_vista(pedido));
        }
        assert(presentacion_pedidos.size() == pedidos.size());
        return presentacion_pedidos;
    }

    PizzasToStrings contadores_to_preparadas(       //
        const modelo::PizzasAContadores &contadores //
    ) {
        PizzasToStrings textos_preparadas;
        for (auto &[tp, contadores_tp] : contadores) {
            assert(has_key(tipo_pizza_to_string, tp));
            auto &nombre_pizza = tipo_pizza_to_string.at(tp);
            std::string linea =
                nombre_pizza + ": " + contadores_tp.preparadas.to_string();
            textos_preparadas[tp] = linea;
        }
        return textos_preparadas;
    }

    VistaPreparacionPizza to_vista(EstadoPreparacionPizzaIndividual preparacion
    ) {
        VistaPreparacionPizza vista;
        vista.nombre_pizza = tipo_pizza_to_string.at(preparacion.tipo);
        vista.porcentaje = preparacion.porcentaje;
        return vista;
    }

    PresentacionPreparacionPizzas estado_preparacion_pizzas_to_vista( //
        const EstadoPreparacionPizzas &preparacion
    ) {
        PresentacionPreparacionPizzas presentacion;
        std::transform(
            preparacion.datos.begin(), preparacion.datos.end(),
            std::back_inserter(presentacion), presentador::to_vista
        );
        return presentacion;
    }

    std::string crea_texto_etiqueta_barra_estado(
        const sf::Time &tiempo_real, const sf::Time &tiempo_juego
    ) {
        static const auto espacios = std::string(7, ' ');
        CadenaJuego cadena(
            "Tiempo Juego: {tiempo_juego}" + espacios +
            "Tiempo Real: {tiempo_real}"
        );
        return cadena
            .interpolar_por_clave("tiempo_juego", time_to_string(tiempo_juego))
            .interpolar_por_clave("tiempo_real", time_to_string(tiempo_real));
    }
} // namespace presentador
