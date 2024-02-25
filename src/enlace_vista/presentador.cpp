#include "presentador.h"
#include "../modelo/dominio.h"
#include "../templates/helpers.h"
#include "../tiempo.h"
#include "../vista/cadenas.h"
#include "../vista/vista_shared.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

namespace presentador {

    namespace impl {
        VistaLinea crea_vista_linea( //
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
            return {s, parte == todo};
        }

        /* Crea una string representando un pedido. Una linea por tipo de pizza,
         * con el formato TipoPizza: actual/objetivo
         */
        std::vector<VistaLinea> pedido_to_vista_lineas(const Pedido &pedido) {
            std::vector<VistaLinea> s;
            size_t ultimo = pedido.contenido.size() - 1;
            size_t i = 0;
            for (auto &[tp, pedido_tp] : pedido.contenido) {
                s.push_back(
                    crea_vista_linea(tp, pedido_tp.servido, pedido_tp.objetivo)
                );
                i++;
            }
            return s;
        }
        /* Crea una vista representando un pedido, que incluye una cadena y el
         * numero de items.
         */
        VistaPedido pedido_to_vista(const Pedido &pedido) {
            auto vista_lineas = pedido_to_vista_lineas(pedido);
            const size_t num_items = pedido.contenido.size();
            assert(num_items == vista_lineas.size());
            return {vista_lineas};
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

    VistaBarraEstado crea_vista_barra_estado(
        const sf::Time &tiempo_real, const sf::Time &tiempo_juego
    ) {
        static const auto espacios = std::string(7, ' ');
        CadenaJuego cadena(
            "Tiempo Juego: {tiempo_juego}" + espacios +
            "Tiempo Real: {tiempo_real}"
        );
        return VistaBarraEstado{
            cadena
                .interpolar_por_clave(
                    "tiempo_juego", tiempo::time_to_string(tiempo_juego)
                )
                .interpolar_por_clave(
                    "tiempo_real", tiempo::time_to_string(tiempo_real)
                )
        };
    }
} // namespace presentador
