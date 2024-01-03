#pragma once

#include "../modelo/dominio.h"
#include <optional>

enum class FaseNivel;

class RealizadorBase {
  protected:
    using NuevaFase = std::optional<FaseNivel>;

  public:
    virtual ~RealizadorBase() = default; // Destructor virtual

    // Metodos virtuales puros
    virtual NuevaFase encargar_pizza(const dominio::TipoPizza tp) = 0;
    virtual NuevaFase despachar_pizza(const dominio::TipoPizza tp) = 0;
    virtual NuevaFase alternar_grid() = 0;
    virtual NuevaFase empezar() = 0;
};
