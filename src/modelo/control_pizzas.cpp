#include "control_pizzas.h"
#include "../templates/helpers.h"
#include <cassert>
#include <iostream>

using modelo::ControlPizzas;

void ControlPizzas::add_pedidos(Pedidos pedidos) {
    this->pedidos = pedidos;
    for (auto &pedido : pedidos) {
        for (auto &[tp, _] : pedido.contenido) {
            if (contadores.find(tp) == contadores.end()) {
                contadores.emplace(tp, Contadores{});
                _tipos_disponibles.push_back(tp);
            }
        }
    }
}

const dominio::TiposDePizza & //
ControlPizzas::get_tipos_disponibles() const {
    return _tipos_disponibles;
}

/*
 * Procesa el despacho de una pizza de tipo tp, incorporandola al primer
 * pedido disponible y evaluando si ya esta completo.
 */
void ControlPizzas::procesar_despacho(const dominio::TipoPizza tp) {
    assert(has_key(contadores, tp));
    auto &contador = contadores.at(tp);
    assert(contador.preparadas > 0);
    contador.preparadas--;
    bool servida = false;
    for (auto &pedido : pedidos) {
        servida = pedido.intentar_servir(tp);
        if (servida) {
            break;
        }
    }
    if (servida) {
        contador.servidas++;
    }
}

int ControlPizzas::obtener_total_preparadas() const {
    int total_preparadas = 0;
    for (auto &[_, contador_tp] : contadores) {
        total_preparadas += contador_tp.preparadas;
    }
    assert(total_preparadas >= 0);
    return total_preparadas;
}

bool ControlPizzas::faltan_pedidos_por_cubrir() const {
    bool faltan = false;
    for (auto &pedido : pedidos) {
        if (!pedido.esta_cubierto()) {
            faltan = true;
            break;
        }
    }
    return faltan;
}

void debug::debug_pedidos(const modelo::Pedidos &pedidos) {
    for (auto &pedido : pedidos) {
        for (auto &[tp, pedido_tp] : pedido.contenido) {
            assert(has_key(tipo_pizza_to_string, tp));
            std::cout << tipo_pizza_to_string.at(tp) << ": "
                      << pedido_tp.objetivo << std::endl;
        }
    }
}
