#pragma once

#include "varios.h"
#include <SFML/Graphics.hpp>

struct BarraProgreso {
  private:
    sf::Vector2f dimensiones;
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;

  public:
    BarraProgreso(
        const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
    );
    void update(int porcentaje);
    void dibujar(sf::RenderWindow &ventana) const;
};

struct BarraProgresoConNombre {
  private:
    sf::Text etiqueta;
    BarraProgreso bp;

  public:
    BarraProgresoConNombre(
        const sf::Vector2f &dimensiones, //
        const std::string &texto,        //
        const sf::Vector2f &posicion,    //
        const sf::Font &font             //
    );
    void update(int porcentaje);
    void dibujar(sf::RenderWindow &ventana) const;
};
