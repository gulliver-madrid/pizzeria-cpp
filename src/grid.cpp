#include "grid.h"
#include <SFML/Graphics.hpp>

void draw_grid(sf::RenderWindow &ventana, int distancia, int tono_gris) {
    sf::Color color(tono_gris, tono_gris, tono_gris);

    for (int j = 0; j < ventana.getSize().y; j += distancia) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(0, j); // Punto de inicio
        line[1].position = sf::Vector2f(ventana.getSize().x, j);
        line[0].color = color;
        line[1].color = color;
        ventana.draw(line);
    }
    for (int i = 0; i < ventana.getSize().x; i += distancia) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(i, 0); // Punto de inicio
        line[1].position = sf::Vector2f(i, ventana.getSize().y);
        line[0].color = color;
        line[1].color = color;
        ventana.draw(line);
    }
}
