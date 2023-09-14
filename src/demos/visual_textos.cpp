#include "visual_textos.h"
#include "../debug.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <iostream>
#include <string>

#define FPS 16
#define FONT_PATH "C:\\Windows\\Fonts\\arial.ttf"

void debug_float_rect(sf::FloatRect rect) {
    std::cout << "getPosition(): " << rect.getPosition().x << ", "
              << rect.getPosition().y << std::endl;
    std::cout << "left: " << rect.left << std::endl;
    std::cout << "top: " << rect.top << std::endl;
    std::cout << "width: " << rect.width << std::endl;
    std::cout << "height: " << rect.height << std::endl;
    std::cout << std::endl;
}

// getGlobalBounds().getPosition() nos da lo mismo que (left, top)
int demo_visual_textos() {
    std::cout << std::endl << "Demo Visual Textos" << std::endl << std::endl;
    sf::RenderWindow window;
    sf::Font font;
    window.create(sf::VideoMode(1800, 920), "Demo visual textos");
    window.setFramerateLimit(FPS);
    if (!font.loadFromFile(FONT_PATH))
        return EXIT_FAILURE;
    int tamano_letra = 128;

    // Representa la línea de abajo
    auto etiqueta_invisible_una_linea =
        sf::Text("Que tal?", font, tamano_letra);
    // Para poder obtener la altura
    sf::FloatRect bounds = etiqueta_invisible_una_linea.getGlobalBounds();
    int altura_linea_abajo = bounds.top + bounds.height;

    sf::Text etiqueta;
    etiqueta.setFont(font);
    etiqueta.setCharacterSize(tamano_letra);
    etiqueta.setFillColor(sf::Color::Yellow);
    etiqueta.setString("Hola mundo\nQue tal?"); // Para poder obtener la altura

    bounds = etiqueta.getGlobalBounds();
    assert(etiqueta.getPosition() == sf::Vector2f(0, 0));
    debug_float_rect(bounds);

    int altura_con_margenes = bounds.top + bounds.height - altura_linea_abajo;
    std::cout << "Altura con margenes: " << altura_con_margenes << std::endl;

    sf::RectangleShape bg_rect(
        sf::Vector2f(bounds.left + bounds.width, altura_con_margenes)
    );
    bg_rect.setPosition(0, 0);
    bg_rect.setFillColor(sf::Color::Blue);

    sf::RectangleShape first_rect(sf::Vector2f(bounds.left, bounds.top));
    first_rect.setFillColor(sf::Color::Red);
    sf::RectangleShape last_rect(sf::Vector2f(bounds.width, bounds.height));
    last_rect.setFillColor(sf::Color::Blue);
    last_rect.setPosition(
        bounds.left + bounds.width, bounds.top + bounds.height
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(bg_rect);
        window.draw(etiqueta);
        window.draw(first_rect);
        window.draw(last_rect);
        window.display();
    }
    return 0;
}
