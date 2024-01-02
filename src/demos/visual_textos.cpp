#include "visual_textos.h"
#include "../debug_sfml.h"
#include "../vista/grid.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <iostream>
#include <string>

#define FPS 16
#define FONT_PATH "C:\\Windows\\Fonts\\arial.ttf"

// getGlobalBounds().getPosition() nos da lo mismo que (left, top)
int demo_visual_textos() {
    std::cout << std::endl << "Demo Visual Textos" << std::endl << std::endl;
    sf::RenderWindow window;
    sf::Font font;
    Grid grid;
    window.create(sf::VideoMode(1800, 920), "Demo visual textos");
    window.setFramerateLimit(FPS);
    if (!font.loadFromFile(FONT_PATH))
        return EXIT_FAILURE;
    int tamano_letra = 128;

    // Representa la linea de abajo
    sf::Text etiqueta_invisible_una_linea("Que tal?", font, tamano_letra);
    // Para poder obtener la altura
    sf::FloatRect bounds = etiqueta_invisible_una_linea.getGlobalBounds();
    int altura_linea_abajo = bounds.top + bounds.height;

    sf::Text etiqueta_dos_lineas("Hola mundo\nQue tal?", font, tamano_letra);
    etiqueta_dos_lineas.setFillColor(sf::Color::Yellow);

    bounds = etiqueta_dos_lineas.getGlobalBounds();
    assert(etiqueta_dos_lineas.getPosition() == sf::Vector2f(0, 0));
    debug::debug_float_rect(bounds);

    // Sin transformaciones, el tamano de los limites locales y
    // globales es el mismo
    assert(bounds.getSize() == etiqueta_dos_lineas.getLocalBounds().getSize());

    int ancho_frase = bounds.left + bounds.width;
    int alto_frase_dos_lineas = bounds.top + bounds.height;

    // Altura con margenes nos da la altura de una linea incluyendo sus margenes
    // superior e inferior
    int altura_con_margenes = alto_frase_dos_lineas - altura_linea_abajo;
    std::cout << "Altura con margenes: " << altura_con_margenes << std::endl;
    std::cout << "font.getLineSpacing(): " << font.getLineSpacing(tamano_letra)
              << std::endl;
    assert(altura_con_margenes == font.getLineSpacing(tamano_letra));

    sf::Vector2f tamano_con_margenes_verticales(
        ancho_frase, altura_con_margenes
    );
    sf::RectangleShape bg_rect(tamano_con_margenes_verticales);
    bg_rect.setFillColor(sf::Color::Blue);

    sf::RectangleShape bg_rect_2(tamano_con_margenes_verticales);
    bg_rect_2.setPosition(0, altura_con_margenes);
    bg_rect_2.setFillColor(sf::Color::Green);

    // Rects que visibilizan los limites
    sf::RectangleShape first_rect(bounds.getPosition());
    first_rect.setFillColor(sf::Color::Red);
    sf::RectangleShape last_rect(bounds.getSize());
    last_rect.setFillColor(sf::Color::Red);
    last_rect.setPosition(ancho_frase, alto_frase_dos_lineas);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        grid.draw(window);
        window.draw(bg_rect);
        window.draw(bg_rect_2);
        window.draw(etiqueta_dos_lineas);
        window.draw(first_rect);
        window.draw(last_rect);
        window.display();
    }
    return 0;
}
