#pragma once

#include "../tiempo.h"
#include "dominio.h"

extern std::map<TipoPizza, float> tiempos_preparacion;

/* Almacena un encargo concreto */
struct EncargoACocina {
  private:
    EncargoACocina(
        const TipoPizza tipo, const TiempoPreparacion tiempo_preparacion
    );

  public:
    const TipoPizza tipo;
    const TiempoPreparacion tiempo_preparacion;
    static EncargoACocina crear(const TipoPizza &tipo, Tiempo tiempo_actual);
};

/* Gestiona la lista de encargos realizados a cocina */
struct Encargos {
  private:
    std::vector<EncargoACocina> _datos;

  public:
    int del_tipo(TipoPizza) const;
    void anadir(const EncargoACocina);
    std::vector<EncargoACocina>::const_iterator begin() const;
    std::vector<EncargoACocina>::const_iterator end() const;
    int total() const;
    EncargoACocina por_indice(int i) const;
};
