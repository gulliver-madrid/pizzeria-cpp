#pragma once

#include "dominio.h"
#include <unordered_map>

struct Encargos;
struct Tiempo;

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
    int objetivo = 0;
};

using PizzasAContadores = std::map<TipoPizza, Contadores>;

/* Pedido relativo a un tipo de pizza */
struct PedidoTipoPizza {
    // Cantidad demandada
    int cantidad;
    // Cantidad servida
    int servido;
};

using Pedido = std::unordered_map<TipoPizza, PedidoTipoPizza>;

void evaluar_preparacion(
    Encargos &encargos, PizzasAContadores &contadores, int maximo,
    Tiempo tiempo_actual
);

struct EstadoPreparacionPizzas {
    std::vector<EstadoPreparacionPizzaIndividual> datos;
    EstadoPreparacionPizzas(const Encargos &encargos);
};
