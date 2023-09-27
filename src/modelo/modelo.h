#pragma once

#include "../tiempo.h"
#include "dominio.h"

extern std::map<TipoPizza, float> tiempos_preparacion;

struct EncargoACocina {
    TipoPizza tipo;
    TiempoPreparacion tiempo_preparacion;
};

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
    int objetivo = 0;
};

using PizzasAContadores = std::map<TipoPizza, Contadores>;

int encargadas_del_tipo(
    const std::vector<EncargoACocina> &encargadas, TipoPizza tipo
);

void evaluar_preparacion(
    std::vector<EncargoACocina> &encargos, PizzasAContadores &contadores,
    int maximo, Tiempo tiempo_actual
);

EncargoACocina crear_encargo(const TipoPizza &tipo, Tiempo tiempo_actual);

extern std::map<TipoPizza, float> tiempos_preparacion;

struct EstadoPreparacionPizzas {
    std::vector<PorcentajeConTipoPizza> porcentajes;
    EstadoPreparacionPizzas(const std::vector<EncargoACocina> &encargos);
};
