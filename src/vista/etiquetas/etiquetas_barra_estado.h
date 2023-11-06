#pragma once

#include "../../shared.h"
#include <SFML/Graphics.hpp>

struct Tiempo;
struct TiempoJuego;

struct EtiquetasBarraEstado : public ObjetoConFont {

  private:
    sf::Text etiqueta;

  public:
    EtiquetasBarraEstado(const sf::Font &);
    void actualizar(const Tiempo &, const TiempoJuego &);
    void dibujar(sf::RenderWindow &ventana) const;
};
