#include "modelo.h"
#include "../tiempo.h"
#include "encargos.h"
#include <cassert>
#include <iostream>
#include <unordered_set>

void debug_contadores(const PizzasAContadores &contadores) {
    std::cout << "Debug contadores" << std::endl;
    for (auto &par : contadores) {
        std::cout << tipo_pizza_to_string[par.first] << " "
                  << "preparadas: " << par.second.preparadas << std::endl;
    }
    std::cout << std::endl;
}

EstadoPreparacionPizzas::EstadoPreparacionPizzas(const Encargos &encargos) {
    assert(datos.empty());
    for (auto &encargo : encargos) {
        datos.push_back(EstadoPreparacionPizzaIndividual{
            encargo.tiempo_preparacion.obtener_porcentaje(), encargo.tipo});
    }
}

/*
 * Evalua si hay pizzas ya preparadas y actualiza encargos y contadores en
 * consecuencia. Las pizzas que lleven más tiempo preparadas pasan antes.
 *
 * [in, out] encargos: Lista de encargos en la cocina
 * [out] contadores: Mapa de contadores para cada tipo de pizza
 * [in] maximo: Número máximo de pizzas que pueden salir de la cocina
 * [in] tiempo_actual: Tiempo actual para comparar con el tiempo de finalización
 * de la preparación
 */
void evaluar_preparacion(
    Encargos &encargos,            //
    PizzasAContadores &contadores, //
    int maximo,                    //
    Tiempo tiempo_actual           //
) {
    // std::cout << "Evaluando preparación" << std::endl;
    size_t i = 0;
    std::vector<std::pair<size_t, int>> pizzas_listas_con_tiempo;
    Encargos restantes;

    // Primera ronda para identificar pizzas listas
    i = 0;
    for (auto &encargo : encargos) {
        Tiempo exceso_tiempo =
            (tiempo_actual - encargo.tiempo_preparacion.finalizacion);
        if (exceso_tiempo >= Tiempo::CERO) {
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
    for (const auto &par : pizzas_listas_con_tiempo) {
        indices_para_pasar.insert(par.first);
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
