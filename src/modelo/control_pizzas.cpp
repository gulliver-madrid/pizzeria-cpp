#include "control_pizzas.h"
#include <iostream>

using modelo::ControlPizzas;

ControlPizzas::ControlPizzas(
    Pedidos pedidos_, const EsSistemaEstatico &es_estatico
)
    : pedidos(pedidos_), es_estatico(es_estatico) {
    for (auto &pedido : pedidos) {
        for (auto &[tp, _] : pedido.contenido) {
            if (contadores.find(tp) == contadores.end()) {
                contadores.emplace(tp, Contadores{});
                _tipos_disponibles.push_back(tp);
            }
        }
    }
    if (es_estatico.valor) {
        assert(pedidos.size() == 1);
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
    auto &contador = contadores.at(tp);
    assert(contador.preparadas > 0);
    contador.preparadas--;
    bool servida = false;
    for (auto &pedido : pedidos) {
        if (pedido.cubierto) {
            continue;
        }
        if (!pedido.incluye(tp)) {
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
    for (auto &[_, contador_tp] : contadores) {
        total_preparadas += contador_tp.preparadas;
    }
    assert(total_preparadas >= 0);
    return total_preparadas;
}

/* Calcular objetivo total. Solo tiene sentido con pedidos estaticos. */
int ControlPizzas::obtener_objetivo_total_estatico() const {
    assert(es_estatico.valor);
    assert(pedidos.size() == 1);
    auto &pedido = pedidos[0];
    int objetivo = 0;
    for (auto &[tp, pedido_tp] : pedido.contenido) {
        assert(contadores.at(tp).preparadas == 0);
        objetivo += pedido_tp.objetivo;
    }
    return objetivo;
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

void debug::debug_pedidos(const modelo::Pedidos &pedidos) {
    for (auto &pedido : pedidos) {
        for (auto &[tp, pedido_tp] : pedido.contenido) {
            std::cout << tipo_pizza_to_string.at(tp) << ": "
                      << pedido_tp.objetivo << std::endl;
        }
    }
}
