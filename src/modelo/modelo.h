#pragma once

#include "../tiempo.h"
#include "dominio.h"
#include <unordered_map>

struct Encargos;

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
    int objetivo = 0;
};

using PizzasAContadores = std::map<TipoPizza, Contadores>;
using Pedido = std::unordered_map<TipoPizza, int>;

void evaluar_preparacion(
    Encargos &encargos, PizzasAContadores &contadores, int maximo,
    Tiempo tiempo_actual
);

struct EstadoPreparacionPizzas {
    std::vector<EstadoPreparacionPizzaIndividual> datos;
    EstadoPreparacionPizzas(const Encargos &encargos);
};
