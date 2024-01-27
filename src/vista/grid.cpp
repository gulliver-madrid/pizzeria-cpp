#include "grid.h"
#include "../shared/types.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <iostream>

void _draw_grid(
    sf::RenderTexture &render_texture, sf::Vector2u tamano_u, int distancia,
    int tono_gris
) {
    sf::Vector2f tamano(
        static_cast<float>(tamano_u.x), static_cast<float>(tamano_u.y)
    );
    assert(tono_gris < 256);
    assert(tono_gris >= 0);
    const auto tono = static_cast<sf::Uint8>(tono_gris);
    sf::Color color(tono, tono, tono);

    // Lineas horizontales
    for (float x = 0; x < tamano.y; x += distancia) {
        sf::RectangleShape rect(sf::Vector2f(tamano.x, 1.0f));
        rect.setFillColor(color);
        rect.setPosition(0, x);
        render_texture.draw(rect);
    }

    // Lineas verticales
    for (float y = 0; y < tamano.x; y += distancia) {
        sf::RectangleShape rect(sf::Vector2f(1.0f, tamano.y));
        rect.setFillColor(color);
        rect.setPosition(y, 0);
        render_texture.draw(rect);
    }
    // Importante!
    render_texture.display();
}

void Grid::draw(sf::RenderTarget &target, int distancia, int tono_gris) {
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
