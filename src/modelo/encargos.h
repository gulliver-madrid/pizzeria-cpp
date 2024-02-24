#pragma once

#include "../shared/types.h"
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

using EncargoACocinaPtr = std::shared_ptr<const EncargoACocina>;

/* Gestiona la lista de encargos realizados a cocina */
struct Encargos {
  private:
    std::vector<EncargoACocinaPtr> _datos;

  public:
    UInt del_tipo(dominio::TipoPizza) const;
    void anadir(EncargoACocinaPtr);
    std::vector<EncargoACocinaPtr>::const_iterator begin() const;
    std::vector<EncargoACocinaPtr>::const_iterator end() const;
    size_t total() const;
    EncargoACocinaPtr por_indice(int i) const;
    bool se_pueden_encargar_mas() const;
};
