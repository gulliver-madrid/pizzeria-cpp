#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define GRID_SIZE 40
#define GRID_TONE 100

struct Grid {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RenderTexture render_texture;
    bool construido = false;
    void
    draw(sf::RenderTarget &(target), int distancia = 50, int tono_gris = 60);
};
