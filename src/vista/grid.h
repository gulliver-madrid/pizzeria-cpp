#pragma once

#include <SFML/Graphics.hpp>

// Grid
#define GRID_SIZE 40
#define GRID_TONE 100

struct Grid {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RenderTexture render_texture;
    bool construido = false;
    void
    draw(sf::RenderWindow &ventana, int distancia = 50, int tono_gris = 60);
};
