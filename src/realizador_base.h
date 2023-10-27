#pragma once

#include <optional>

enum class FaseNivel;

class RealizadorBase {
  public:
    using NuevaFase = std::optional<FaseNivel>;

    virtual ~RealizadorBase() = default; // Destructor virtual

    // Métodos virtuales puros
    virtual NuevaFase encargar_pizza(const dominio::TipoPizza tp) = 0;
    virtual NuevaFase despachar_pizza(const dominio::TipoPizza tp) = 0;
    virtual NuevaFase alternar_grid() = 0;
    virtual NuevaFase empezar() = 0;
};
