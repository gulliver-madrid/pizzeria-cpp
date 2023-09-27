#include "modelo.h"
#include <cassert>
#include <unordered_set>

// En segundos
std::map<TipoPizza, float> tiempos_preparacion = {
    {TipoPizza::Margarita, 2.5f},
    {TipoPizza::Pepperoni, 4.0f},
    {TipoPizza::CuatroQuesos, 7.0f},
};

void EstadoPreparacionPizzas::actualizar(
    const std::vector<EncargoACocina> &encargos
) {
    assert(porcentajes.empty());
    for (auto &encargo : encargos) {
        porcentajes.push_back(PorcentajeConTipoPizza{
            encargo.tiempo_preparacion.obtener_porcentaje(), encargo.tipo});
    }
}

int encargadas_del_tipo(
    const std::vector<EncargoACocina> &encargadas, TipoPizza tipo
) {
    int c = 0;
    for (auto &encargo : encargadas) {
        if (encargo.tipo == tipo) {
            c++;
        }
    }
    return c;
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
    std::vector<EncargoACocina> &encargos, //
    PizzasAContadores &contadores,         //
    int maximo,                            //
    Tiempo tiempo_actual                   //
) {
    std::vector<std::pair<size_t, int>> pizzas_listas_con_tiempo;
    std::vector<EncargoACocina> restantes;

    // Primera ronda para identificar pizzas listas
    for (size_t i = 0; i < encargos.size(); i++) {
        const auto &encargo = encargos[i];
        Tiempo exceso_tiempo =
            (tiempo_actual - encargo.tiempo_preparacion.finalizacion);
        if (exceso_tiempo >= Tiempo::CERO) {
            pizzas_listas_con_tiempo.push_back(
                {i, exceso_tiempo.obtener_milisegundos()}
            );
        }
    }

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
    for (size_t i = 0; i < encargos.size(); i++) {
        const auto &encargo = encargos[i];
        if (indices_para_pasar.find(i) != indices_para_pasar.end()) {
            contadores[encargo.tipo].preparadas++;
        } else {
            restantes.push_back(encargo);
        }
    }

    encargos = std::move(restantes);
}

EncargoACocina crear_encargo(const TipoPizza &tipo, Tiempo tiempo_actual) {
    auto total = Tiempo::desde_segundos(tiempos_preparacion[tipo]);
    return EncargoACocina{
        tipo, //
        TiempoPreparacion{
            tiempo_actual + total, total //
        }};
}
