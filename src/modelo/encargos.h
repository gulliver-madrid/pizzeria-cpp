#pragma once

#include "../tiempo.h"
#include <vector>

namespace dominio {
    enum class TipoPizza;
}

/* Almacena un encargo concreto */
struct EncargoACocina {
    const dominio::TipoPizza tipo;
    const TiempoPreparacion tiempo_preparacion;
    EncargoACocina(
        const dominio::TipoPizza tipo,
        const sf::Time &tiempo_actual = sf::Time::Zero
    );
};

/* Gestiona la lista de encargos realizados a cocina */
struct Encargos {
  private:
    std::vector<EncargoACocina> _datos;

  public:
    int del_tipo(dominio::TipoPizza) const;
    void anadir(const EncargoACocina);
    std::vector<EncargoACocina>::const_iterator begin() const;
    std::vector<EncargoACocina>::const_iterator end() const;
    int total() const;
    EncargoACocina por_indice(int i) const;
};
