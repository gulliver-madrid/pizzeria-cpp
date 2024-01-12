#include "presentador.h"
#include "../modelo/dominio.h"
#include "../templates/helpers.h"
#include "vista_shared.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

namespace presentador {
    std::string crea_linea_completitud_pizza(
        const dominio::TipoPizza tp, int parte, int todo
    ) {
        assert(has_key(tipo_pizza_to_string, tp));
        const auto nombre_pizza = tipo_pizza_to_string.at(tp);
        std::string s = (           //
            nombre_pizza + ": " +   //
            std::to_string(parte) + //
            std::string("/") +      //
            std::to_string(todo)    //
        );
        return s;
    }

    /* Crea una string representando un pedido. Una linea por tipo de pizza, con
     * el formato TipoPizza: actual/objetivo
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

    VistaPizzasToStrings contadores_to_preparadas(  //
        const modelo::PizzasAContadores &contadores //
    ) {
        VistaPizzasToStrings textos_preparadas;
        for (auto &[tp, contadores_tp] : contadores) {
            assert(has_key(tipo_pizza_to_string, tp));
            auto &nombre_pizza = tipo_pizza_to_string.at(tp);
            std::string linea =
                nombre_pizza + ": " + std::to_string(contadores_tp.preparadas);
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

    std::vector<VistaPreparacionPizza> estado_preparacion_pizzas_to_vista( //
        const EstadoPreparacionPizzas &preparacion
    ) {
        std::vector<VistaPreparacionPizza> vista_preparaciones_pizzas;
        std::transform(
            preparacion.datos.begin(), preparacion.datos.end(),
            std::back_inserter(vista_preparaciones_pizzas),
            presentador::to_vista
        );
        return vista_preparaciones_pizzas;
    }
} // namespace presentador
