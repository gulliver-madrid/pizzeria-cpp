#include "control_pizzas.h"
#include <iostream>

void debug_pedidos(const Pedidos &pedidos) {
    for (auto &pedido : pedidos) {
        for (auto &par : pedido.contenido) {
            std::cout << tipo_pizza_to_string[par.first] << ": "
                      << par.second.objetivo << std::endl;
        }
    }
}

ControlPizzas::ControlPizzas(Pedidos pedidos_, bool es_estatico_)
    : pedidos(pedidos_), es_estatico(es_estatico_) {
    for (auto &pedido : pedidos) {
        for (auto &par : pedido.contenido) {
            auto &tp = par.first;
            if (contadores.find(tp) == contadores.end()) {
                contadores[tp] = Contadores{};
                _tipos_disponibles.push_back(tp);
            }
        }
    }
}

const std::vector<TipoPizza> &ControlPizzas::get_tipos_disponibles() const {
    return _tipos_disponibles;
}
