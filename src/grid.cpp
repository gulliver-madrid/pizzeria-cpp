#include "grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void _draw_grid(
    sf::RenderTexture &render_texture, sf::Vector2u tamano_u, int distancia,
    int tono_gris
) {
    sf::Vector2i tamano(
        static_cast<int>(tamano_u.x), static_cast<int>(tamano_u.y)
    );

    sf::Color color(tono_gris, tono_gris, tono_gris);
    std::cout << "Rendering grid" << std::endl;

    // Líneas horizontales
    for (int j = 0; j < tamano.y; j += distancia) {
        sf::RectangleShape rect(sf::Vector2f(tamano.x, 1));
        rect.setFillColor(color);
        rect.setPosition(0, j);
        render_texture.draw(rect);
    }

    // Líneas verticales
    for (int i = 0; i < tamano.x; i += distancia) {
        sf::RectangleShape rect(sf::Vector2f(1, tamano.y));
        rect.setFillColor(color);
        rect.setPosition(i, 0);
        render_texture.draw(rect);
    }
    // Importante!
    render_texture.display();
}

void draw_grid(
    sf::RenderWindow &ventana, Grid &grid, int distancia, int tono_gris
) {
    // Verificamos si ya se ha creado la textura
    bool diff_tamano =
        (grid.texture.getSize().x != ventana.getSize().x ||
         grid.texture.getSize().y != ventana.getSize().y);
    if (diff_tamano && !grid.construido) {
        grid.renderTexture.create(ventana.getSize().x, ventana.getSize().y);
        // Si no, la creamos con el tamaño de la ventana
        _draw_grid(grid.renderTexture, ventana.getSize(), distancia, tono_gris);
        grid.texture = grid.renderTexture.getTexture();
        grid.sprite.setTexture(grid.texture);
        grid.construido = true;
    }
    ventana.draw(grid.sprite);
}
