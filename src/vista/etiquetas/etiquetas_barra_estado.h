#pragma once

#include <SFML/Graphics.hpp>

struct EtiquetasBarraEstado {

  private:
    const sf::Font &font;
    sf::Text etiqueta;

  public:
    EtiquetasBarraEstado(const sf::Font &);
    void actualizar();
    void dibujar(sf::RenderWindow &ventana) const;
};
