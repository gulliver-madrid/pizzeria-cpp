#include "manejo_rutas.h"
#include "paths.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 920), "Pizzería");
    window.setFramerateLimit(60);

    // Contador
    int contador = 0;

    // Fuente
    sf::Font font;
    if (!font.loadFromFile(getResourcePath(FONT_PATH).string())) {
        std::cout << "No se encontró ninguna fuente válida en \"" << FONT_PATH
                  << "\". Por favor, proporcione una fuente en esa ruta para "
                     "ejecutar el programa."
                  << std::endl;
        return EXIT_FAILURE;
    }

    // Texto para el contador
    sf::Text texto;
    texto.setFont(font);
    texto.setCharacterSize(48);
    texto.setPosition(50, 50);
    texto.setFillColor(sf::Color::White);

    // Botón para reducir el contador
    sf::RectangleShape botonReducir(sf::Vector2f(150, 50));
    botonReducir.setFillColor(sf::Color::Red);
    botonReducir.setPosition(50, 150);

    // Botón para incrementar el contador
    sf::RectangleShape botonAumentar(sf::Vector2f(150, 50));
    botonAumentar.setFillColor(sf::Color::Green);
    botonAumentar.setPosition(250, 150);

    // Texto del botón Reducir
    sf::Text textoBotonReducir;
    textoBotonReducir.setFont(font);
    textoBotonReducir.setCharacterSize(24);
    textoBotonReducir.setFillColor(sf::Color::White);
    textoBotonReducir.setString("Reducir");
    textoBotonReducir.setPosition(60, 160);

    // Texto del botón Aumentar
    sf::Text textoBotonAumentar;
    textoBotonAumentar.setFont(font);
    textoBotonAumentar.setCharacterSize(24);
    textoBotonAumentar.setFillColor(sf::Color::White);
    textoBotonAumentar.setString("Aumentar");
    textoBotonAumentar.setPosition(260, 160);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cierre de ventana
            if (event.type == sf::Event::Closed)
                window.close();

            // Pulsación botón
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::FloatRect botonAumentarBounds =
                    botonAumentar.getGlobalBounds();
                sf::FloatRect botonReducirBounds =
                    botonReducir.getGlobalBounds();

                if (botonAumentarBounds.contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y)
                    )) {
                    contador++;
                }

                if (botonReducirBounds.contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y)
                    )) {
                    contador--;
                }
            }
        }

        texto.setString("Contador: " + std::to_string(contador));

        window.clear();
        window.draw(texto);
        window.draw(botonAumentar);
        window.draw(textoBotonAumentar);
        window.draw(botonReducir);
        window.draw(textoBotonReducir);
        window.display();
    }

    return 0;
}
