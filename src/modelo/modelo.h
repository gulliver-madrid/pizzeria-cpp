#pragma once

#include "../tiempo.h"
#include "dominio.h"

extern std::map<TipoPizza, float> tiempos_preparacion;

struct EncargoACocina {
    TipoPizza tipo;
    TiempoPreparacion tiempo_preparacion;
};

struct Encargos {
    std::vector<EncargoACocina> datos;
    int del_tipo(TipoPizza) const;
};

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
    int objetivo = 0;
};

using PizzasAContadores = std::map<TipoPizza, Contadores>;

void evaluar_preparacion(
    Encargos &encargos, PizzasAContadores &contadores, int maximo,
    Tiempo tiempo_actual
);

EncargoACocina crear_encargo(const TipoPizza &tipo, Tiempo tiempo_actual);

extern std::map<TipoPizza, float> tiempos_preparacion;

struct EstadoPreparacionPizzas {
    std::vector<EstadoPreparacionPizzaIndividual> datos;
    EstadoPreparacionPizzas(const Encargos &encargos);
};
