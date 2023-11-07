#include "modelo.h"
#include "encargos.h"
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

EstadoPreparacionPizzas::EstadoPreparacionPizzas(
    const Encargos &encargos,        //
    const TiempoJuego &tiempo_actual //
) {
    assert(datos.empty());
    for (auto &encargo : encargos) {
        datos.push_back(EstadoPreparacionPizzaIndividual{
            encargo.tiempo_preparacion.obtener_porcentaje(tiempo_actual),
            encargo.tipo
        });
    }
}

PedidoTipoPizza::PedidoTipoPizza(int objetivo) : objetivo(objetivo) {
    assert(objetivo >= 0);
}
PedidoTipoPizza::PedidoTipoPizza(int servido, int objetivo)
    : servido(servido), objetivo(objetivo) {
    assert(objetivo >= 0);
    assert(servido >= 0);
    assert(servido <= objetivo);
}

Pedido::Pedido(ContenidoPedido &&contenido) : contenido(std::move(contenido)) {}

void Pedido::evaluar() {
    bool faltan = false;
    for (auto &[_, pedido_tp] : contenido) {
        if (pedido_tp.servido < pedido_tp.objetivo) {
            faltan = true;
            break;
        }
    }
    if (!faltan) {
        cubierto = true;
    }
}

bool Pedido::incluye(dominio::TipoPizza tp) { //
    return contenido.count(tp) > 0;
}

/*
 * Evalua si hay pizzas ya preparadas y actualiza encargos y contadores en
 * consecuencia. Las pizzas que lleven más tiempo preparadas pasan antes.
 *
 * [in, out] encargos: Lista de encargos en la cocina
 * [out] contadores: Mapa de contadores para cada tipo de pizza
 * [in] maximo: Número máximo de pizzas que pueden salir de la cocina
 * [in] tiempo_actual: TiempoJuego actual para comparar con el tiempo de
 * finalización de la preparación
 */
void evaluar_preparacion(
    Encargos &encargos,                    //
    modelo::PizzasAContadores &contadores, //
    int maximo,                            //
    const TiempoJuego &tiempo_actual       //
) {
    // std::cout << "Evaluando preparación" << std::endl;
    size_t i = 0;
    std::vector<std::pair<size_t, int>> pizzas_listas_con_tiempo;
    Encargos restantes;

    // Primera ronda para identificar pizzas listas
    i = 0;
    for (auto &encargo : encargos) {
        TiempoJuego exceso_tiempo =
            (tiempo_actual - encargo.tiempo_preparacion.finalizacion);
        if (exceso_tiempo >= TiempoJuego_CERO) {
            pizzas_listas_con_tiempo.push_back(
                {i, exceso_tiempo.obtener_milisegundos()}
            );
        }
        i++;
    }

    // std::cout << "Se detectaron " << pizzas_listas_con_tiempo.size()
    //           << " pizzas listas" << std::endl;

    // Ordenar y limitar las pizzas que pueden salir
    if (pizzas_listas_con_tiempo.size() > maximo) {
        // Ordenamos la lista de manera descendente para que
        // las que llevan más tiempo preparadas salgan antes
        std::sort(
            pizzas_listas_con_tiempo.begin(), pizzas_listas_con_tiempo.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; }
        );
        pizzas_listas_con_tiempo.resize(maximo);
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
