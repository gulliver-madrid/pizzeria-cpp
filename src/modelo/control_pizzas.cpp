#include "control_pizzas.h"
#include <iostream>

namespace debug {
    void debug_pedidos(const Pedidos &pedidos) {
        for (auto &pedido : pedidos) {
            for (auto &par : pedido.contenido) {
                std::cout << tipo_pizza_to_string[par.first] << ": "
                          << par.second.objetivo << std::endl;
            }
        }
    }
} // namespace debug

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
    if (es_estatico) {
        assert(pedidos.size() == 1);
    }
}

const std::vector<TipoPizza> & //
ControlPizzas::get_tipos_disponibles() const {
    return _tipos_disponibles;
}

/*
 * Procesa el despacho de una pizza de tipo tp, incorporandola al primer
 * pedido disponible y evaluando si ya esta completo.
 */
void ControlPizzas::procesar_despacho(const TipoPizza tp) {
    auto &contador = contadores.at(tp);
    assert(contador.preparadas > 0);
    contador.preparadas--;
    bool servida = false;
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
        servida = true;
        break;
    }

    if (servida) {
        contador.servidas++;
    }
}

int ControlPizzas::obtener_total_preparadas() const {
    int total_preparadas = 0;
    for (auto &par : contadores) {
        auto contador_tp = par.second;
        total_preparadas += contador_tp.preparadas;
    }
    assert(total_preparadas >= 0);
    return total_preparadas;
}

/* Calcular total objetivos. Solo tiene sentido con pedidos estaticos. */
int ControlPizzas::obtener_total_objetivos() const {
    assert(es_estatico);
    assert(pedidos.size() == 1);
    auto &pedido = pedidos[0];
    int total_objetivos = 0;
    for (auto &par : pedido.contenido) {
        auto tp = par.first;
        auto pedido_tp = par.second;
        assert(contadores.at(tp).preparadas == 0);
        total_objetivos += pedido_tp.objetivo;
    }
    return total_objetivos;
}
bool ControlPizzas::faltan_pedidos_por_cubrir() const {
    bool faltan = false;
    for (auto &pedido : pedidos) {
        if (!pedido.cubierto) {
            faltan = true;
            break;
        }
    }
    return faltan;
}
