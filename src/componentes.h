#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct BotonConTexto {
    sf::RectangleShape boton;
    sf::Text texto;
    bool activo = true;
    bool visible = false;
    bool colisiona(sf::Vector2i &mousePos);
    void dibujar(sf::RenderWindow &window);
};
