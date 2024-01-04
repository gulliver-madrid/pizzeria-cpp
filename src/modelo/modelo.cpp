#include "modelo.h"
#include "encargos.h"
#include <algorithm> // sort
#include <iostream>
#include <unordered_set>

namespace debug {
    void debug_contadores(const modelo::PizzasAContadores &contadores) {
        using namespace std;
        cout << "Debug contadores" << endl;
        for (auto &[tp, contadores_tp] : contadores) {
            cout << tipo_pizza_to_string.at(tp) << " "
                 << "preparadas: " << contadores_tp.preparadas << endl;
        }
        cout << endl;
    }
} // namespace debug

EstadoPreparacionPizzas::EstadoPreparacionPizzas(
    const Encargos &encargos,     //
    const sf::Time &tiempo_actual //
) {
    assert(datos.empty());
    for (auto &encargo : encargos) {
        datos.push_back(EstadoPreparacionPizzaIndividual{
            encargo.tiempo_preparacion.obtener_porcentaje(tiempo_actual),
            encargo.tipo
        });
    }
}

//////// PedidoTipoPizza

PedidoTipoPizza::PedidoTipoPizza(int objetivo) : objetivo(objetivo) {
    assert(objetivo >= 0);
}
PedidoTipoPizza::PedidoTipoPizza(int servido, int objetivo)
    : servido(servido), objetivo(objetivo) {
    assert(objetivo >= 0);
    assert(servido >= 0);
    assert(servido <= objetivo);
}

bool PedidoTipoPizza::cubierto() const {
    assert(servido <= objetivo);
    return servido == objetivo;
}

//////// Pedido

Pedido::Pedido(ContenidoPedido &&contenido) : contenido(std::move(contenido)) {}

/* Evalua si el pedido esta cubierto */
void Pedido::evaluar() {
    bool faltan = false;
    for (auto &[_, pedido_tp] : contenido) {
        if (!pedido_tp.cubierto()) {
            faltan = true;
            break;
        }
    }
    if (!faltan) {
        cubierto = true;
    }
}

bool Pedido::incluye(dominio::TipoPizza tp) const { //
    return contenido.count(tp) > 0;
}

bool Pedido::esta_cubierto() const { //
    return cubierto;
}

bool Pedido::intentar_servir(const dominio::TipoPizza tp) {
    if (cubierto) {
        return false;
    }
    if (!incluye(tp)) {
        return false;
    }
    auto &pedido_tp = contenido.at(tp);
    if (pedido_tp.cubierto()) {
        return false;
    }
    pedido_tp.servido++;
    evaluar();
    return true;
}

/*
 * Evalua si hay pizzas ya preparadas y actualiza encargos y contadores en
 * consecuencia. Las pizzas que lleven mas tiempo preparadas pasan antes.
 *
 * [in, out] encargos: Lista de encargos en la cocina
 * [out] contadores: Mapa de contadores para cada tipo de pizza
 * [in] preparables: Numero maximo de pizzas que pueden salir de la cocina
 * [in] tiempo_actual: sf::Time actual para comparar con el tiempo de
 * finalizacion de la preparacion
 */
void evaluar_preparacion(
    Encargos &encargos,                    //
    modelo::PizzasAContadores &contadores, //
    int preparables,                       //
    const sf::Time &tiempo_actual          //
) {
    size_t i = 0;
    std::vector<std::pair<size_t, int>> pizzas_listas_con_tiempo;
    Encargos restantes;

    // Primera ronda para identificar pizzas listas
    i = 0;
    for (auto &encargo : encargos) {
        sf::Time exceso_tiempo =
            (tiempo_actual - encargo.tiempo_preparacion.finalizacion);
        if (exceso_tiempo >= sf::Time::Zero) {
            pizzas_listas_con_tiempo.push_back(
                {i, exceso_tiempo.asMilliseconds()}
            );
        }
        i++;
    }

    // Ordenar y limitar las pizzas que pueden salir
    if (pizzas_listas_con_tiempo.size() > preparables) {
        // Ordenamos la lista de manera descendente para que
        // las que llevan mas tiempo preparadas salgan antes
        std::sort(
            pizzas_listas_con_tiempo.begin(), pizzas_listas_con_tiempo.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; }
        );
        pizzas_listas_con_tiempo.resize(preparables);
    }

    std::unordered_set<size_t> indices_para_pasar;
    for (const auto &[indice, _] : pizzas_listas_con_tiempo) {
        indices_para_pasar.insert(indice);
    }

    // Segunda ronda para actualizar contadores y lista de encargos
    i = 0;
    for (auto &encargo : encargos) {
        if (indices_para_pasar.find(i) != indices_para_pasar.end()) {
            contadores[encargo.tipo].preparadas++;
        } else {
            restantes.anadir(encargo);
        }
        i++;
    }

    encargos = std::move(restantes);
}
