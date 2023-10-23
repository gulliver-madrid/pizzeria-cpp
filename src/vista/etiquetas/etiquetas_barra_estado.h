#pragma once

#include <SFML/Graphics.hpp>

struct Tiempo;
struct TiempoJuego;

struct EtiquetasBarraEstado {

  private:
    const sf::Font &font;
    sf::Text etiqueta;

  public:
    EtiquetasBarraEstado(const sf::Font &);
    void actualizar(const Tiempo &, const TiempoJuego &);
    void dibujar(sf::RenderWindow &ventana) const;
};
