#include "presentador.h"

#include "../modelo/dominio.h"
#include "../modelo/modelo.h"

std::string
crea_linea_completitud_pizza(const TipoPizza &tp, int parte, int todo) {
    const auto nombre_pizza = tipo_pizza_to_string.at(tp);
    std::string s = (           //
        nombre_pizza + ": " +   //
        std::to_string(parte) + //
        std::string("/") +      //
        std::to_string(todo)    //
    );
    return s;
}

/* Crea una string representando un pedido. Una línea por tipo de pizza, con el
 * formato TipoPizza: actual/objetivo
 */
std::string pedido_to_string(const Pedido &pedido) {
    std::string s;
    size_t ultimo = pedido.contenido.size() - 1;
    size_t i = 0;
    for (auto &par : pedido.contenido) {
        s.append(
            crea_linea_completitud_pizza(
                par.first, par.second.servido, par.second.objetivo
            ) +
            ((i < ultimo) ? "\n" : "")
        );
        i++;
    }
    return s;
}
