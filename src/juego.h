#pragma once

#include <SFML/Graphics.hpp>

int juego();

struct TitulosPaneles {
    sf::Text en_preparacion;
    sf::Text preparadas;
    sf::Text pedidos;
    bool visible = false;
    void dibujar(sf::RenderWindow &window);
};
