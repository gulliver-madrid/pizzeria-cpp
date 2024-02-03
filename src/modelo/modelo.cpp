#include "modelo.h"
#include "../templates/helpers.h"
#include "encargos.h"
#include <algorithm> // sort
#include <cassert>
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

///////////////////////////////////////////
// EstadoPreparacionPizzas
//////////////////////////////////////////

EstadoPreparacionPizzas::EstadoPreparacionPizzas(
    const Encargos &encargos,     //
    const sf::Time &tiempo_actual //
) {
    assert(datos.empty());
    for (auto &encargo : encargos) {
        datos.push_back(EstadoPreparacionPizzaIndividual{
            encargo->tiempo_preparacion.obtener_porcentaje(tiempo_actual),
            encargo->tipo
        });
    }
}

///////////////////////////////////////////
// LineaPedido
//////////////////////////////////////////

LineaPedido::LineaPedido() {}
LineaPedido::LineaPedido(UInt objetivo) : objetivo(objetivo) {
    assert(objetivo >= 0);
}
LineaPedido::LineaPedido(UInt servido, UInt objetivo)
    : servido(servido), objetivo(objetivo) {
    assert(objetivo >= 0);
    assert(servido >= 0);
    assert(servido <= objetivo);
}

bool LineaPedido::esta_cubierto() const {
    assert(servido <= objetivo);
    return servido == objetivo;
}

///////////////////////////////////////////
// Pedido
//////////////////////////////////////////

Pedido::Pedido(ContenidoPedido contenido) : contenido(contenido) {}

/* Evalua si el pedido esta cubierto */
void Pedido::evaluar() {
    bool faltan = false;
    for (auto &[_, pedido_tp] : contenido) {
        if (!pedido_tp.esta_cubierto()) {
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
    assert(has_key(contenido, tp));
    auto &pedido_tp = contenido.at(tp);
    if (pedido_tp.esta_cubierto()) {
        return false;
    }
    pedido_tp.servido++;
    evaluar();
    return true;
}

///////////////////////////////////////////
// evaluar_preparacion()
//////////////////////////////////////////

/*
 * Guarda el puntero al encargo junto con el tiempo que lleva preparada la pizza
 */
struct PreparadaConTiempo {
    EncargoACocinaPtr encargo;
    sf::Int32 milisegundos;
};

/* Identifica las pizzas listas con el tiempo que llevan preparadas */
std::vector<PreparadaConTiempo> obtener_preparadas_con_tiempo(
    const Encargos &encargos, const sf::Time &tiempo_actual
) {
    std::vector<PreparadaConTiempo> preparadas;
    for (const auto &encargo : encargos) {
        auto &finalizacion = encargo->tiempo_preparacion.finalizacion;
        sf::Time exceso_tiempo = (tiempo_actual - finalizacion);
        if (exceso_tiempo >= sf::Time::Zero) {
            const auto &tiempo_preparada = exceso_tiempo.asMilliseconds();
            preparadas.push_back({encargo, tiempo_preparada});
        }
    }
    return preparadas;
}

/* Ordenar y limitar las pizzas que pueden salir de cocina */
void ordenar_y_limitar_preparadas(
    std::vector<PreparadaConTiempo> &preparadas, const UInt &maximo_uint
) {
    int maximo = maximo_uint.to_int();
    if (preparadas.size() > maximo) {
        // Ordenamos la lista de manera descendente para que
        // las que llevan mas tiempo preparadas salgan antes
        ordenar_por_criterio(
            preparadas,
            [](const PreparadaConTiempo &a, const PreparadaConTiempo &b) {
                return a.milisegundos > b.milisegundos;
            }
        );
        preparadas.resize(maximo);
    }
}

/*
 * Evalua si hay pizzas ya preparadas y actualiza encargos y contadores en
 * consecuencia. Las pizzas que lleven mas tiempo preparadas pasan antes de
 * de la cocina al area de preparadas.
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
    const UInt preparables,                //
    const sf::Time &tiempo_actual          //
) {
    // Identifica pizzas listas para pasar al area de preparadas
    std::vector<PreparadaConTiempo> preparadas =
        obtener_preparadas_con_tiempo(encargos, tiempo_actual);

    ordenar_y_limitar_preparadas(preparadas, preparables);

    std::unordered_set<EncargoACocinaPtr> encargos_a_pasar;
    for (const auto &preparada : preparadas) {
        encargos_a_pasar.insert(preparada.encargo);
    }

    // Actualiza contadores y lista de encargos
    Encargos restantes;
    for (auto &encargo : encargos) {
        if (contiene(encargos_a_pasar, encargo)) {
            // Si no existe el contador para ese tipo de pizza, se crea
            contadores[encargo->tipo].preparadas++;
        } else {
            restantes.anadir(encargo);
        }
    }

    encargos = std::move(restantes);
}
