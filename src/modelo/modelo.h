#pragma once

#include "../tiempo.h"
#include "dominio.h"

extern std::map<TipoPizza, float> tiempos_preparacion;

struct EncargoACocina {
    TipoPizza tipo;
    TiempoPreparacion tiempo_preparacion;
};

struct Encargos {
  private:
    std::vector<EncargoACocina> _datos;

  public:
    int del_tipo(TipoPizza) const;
    void anadir(const EncargoACocina);
    std::vector<EncargoACocina>::const_iterator begin() const;
    std::vector<EncargoACocina>::const_iterator end() const;
    int total() const;
    EncargoACocina at(int i) const;
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
