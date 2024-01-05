#include "grid.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <iostream>

void _draw_grid(
    sf::RenderTexture &render_texture, sf::Vector2u tamano_u, int distancia,
    int tono_gris
) {
    sf::Vector2i tamano(
        static_cast<int>(tamano_u.x), static_cast<int>(tamano_u.y)
    );

    sf::Color color(tono_gris, tono_gris, tono_gris);

    // Lineas horizontales
    for (int j = 0; j < tamano.y; j += distancia) {
        sf::RectangleShape rect(sf::Vector2f(tamano.x, 1));
        rect.setFillColor(color);
        rect.setPosition(0, j);
        render_texture.draw(rect);
    }

    // Lineas verticales
    for (int i = 0; i < tamano.x; i += distancia) {
        sf::RectangleShape rect(sf::Vector2f(1, tamano.y));
        rect.setFillColor(color);
        rect.setPosition(i, 0);
        render_texture.draw(rect);
    }
    // Importante!
    render_texture.display();
}

void Grid::draw(sf::RenderTarget &(target), int distancia, int tono_gris) {
    // Verificamos si ya se ha creado la textura
    bool diff_tamano =
        (texture.getSize().x != target.getSize().x ||
         texture.getSize().y != target.getSize().y);
    if (diff_tamano && !construido) {
        render_texture.create(target.getSize().x, target.getSize().y);
        // Si no, la creamos con el tamano del target (normalmente la ventana)
        _draw_grid(render_texture, target.getSize(), distancia, tono_gris);
        texture = render_texture.getTexture();
        sprite.setTexture(texture);
        construido = true;
    }
    target.draw(sprite);
}
