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
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(0, j); // Punto de inicio
        line[1].position = sf::Vector2f(render_texture.getSize().x, j);
        line[0].color = color;
        line[1].color = color;
        render_texture.draw(line);
    }

    // Líneas verticales
    for (int i = 0; i < tamano.x; i += distancia) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(i, 0); // Punto de inicio
        line[1].position = sf::Vector2f(i, render_texture.getSize().y);
        line[0].color = color;
        line[1].color = color;
        render_texture.draw(line);
    }
    // Importante!
    render_texture.display();
}

void draw_grid(
    sf::RenderWindow &ventana, Grid &grid, int distancia, int tono_gris
) {
    std::cout << ventana.getSize().x << std::endl;
    // Verificamos si ya se ha creado la textura
    if (grid.texture.getSize().x != ventana.getSize().x ||
        grid.texture.getSize().y != ventana.getSize().y) {
        sf::RenderTexture renderTexture;
        renderTexture.create(ventana.getSize().x, ventana.getSize().y);
        // Si no, la creamos con el tamaño de la ventana
        _draw_grid(renderTexture, ventana.getSize(), distancia, tono_gris);
        grid.texture = renderTexture.getTexture();
        grid.sprite.setTexture(grid.texture);
    }
    ventana.draw(grid.sprite);
}
