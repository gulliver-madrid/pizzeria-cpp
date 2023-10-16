#pragma once

#include "../tiempo.h"

namespace modelo {
    enum class TipoPizza;
}

/* Almacena un encargo concreto */
struct EncargoACocina {
    const modelo::TipoPizza tipo;
    const TiempoPreparacion tiempo_preparacion;
    EncargoACocina(const modelo::TipoPizza tipo, const Tiempo tiempo_actual);
};

/* Gestiona la lista de encargos realizados a cocina */
struct Encargos {
  private:
    std::vector<EncargoACocina> _datos;

  public:
    int del_tipo(modelo::TipoPizza) const;
    void anadir(const EncargoACocina);
    std::vector<EncargoACocina>::const_iterator begin() const;
    std::vector<EncargoACocina>::const_iterator end() const;
    int total() const;
    EncargoACocina por_indice(int i) const;
};
