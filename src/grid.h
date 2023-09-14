#pragma once

#include <SFML/Graphics.hpp>

struct Grid {
    sf::Sprite sprite;
    sf::Texture texture;
};

void draw_grid(
    sf::RenderWindow &ventana, Grid &grid, int distancia = 50,
    int tono_gris = 60
);
