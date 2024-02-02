#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define GRID_SIZE 40
#define GRID_TONE 100

class Grid {
  private:
    bool construido = false;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RenderTexture render_texture;

  public:
    void draw(sf::RenderTarget &, int distancia = 50, int tono_gris = 60);
};
