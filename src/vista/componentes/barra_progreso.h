#pragma once

#include <SFML/Graphics.hpp>

struct BarraProgreso {
  private:
    sf::Vector2f dimensiones = {0, 0};

  public:
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
    void setup(const sf::Vector2f &dimensiones_, const sf::Vector2f &posicion);
    void update(int porcentaje);
};

struct BarraProgresoConNombre {
  private:
    sf::Text etiqueta;
    BarraProgreso bp;

  public:
    void setup(
        const sf::Vector2f &dimensiones, //
        const std::string &texto,        //
        const sf::Vector2f &posicion,    //
        const sf::Font &font             //
    );
    void update(int porcentaje);
    void dibujar(sf::RenderWindow &ventana) const;
};
