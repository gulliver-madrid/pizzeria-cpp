#pragma once

#include <SFML/Graphics.hpp>

// Grid
#define DRAW_GRID 1
#define GRID_SIZE 40
#define GRID_TONE 100

struct Grid {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RenderTexture renderTexture;
    bool construido = false;
};

void draw_grid(
    sf::RenderWindow &ventana, Grid &grid, int distancia = 50,
    int tono_gris = 60
);
