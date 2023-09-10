#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "paths.h"
#include "manejo_rutas.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 920), "Pizzería");
    window.setFramerateLimit(60);

    // Contador
    int contador = 0;

    // Fuente
    sf::Font font;
    if (!font.loadFromFile(getResourcePath(FONT_PATH).string()))
    {
        std::cout << "No se encontró ninguna fuente válida en \"" << FONT_PATH << "\". Por favor, proporcione una fuente en esa ruta para ejecutar el programa." << std::endl;
        return EXIT_FAILURE;
    }

    // Texto para el contador
    sf::Text texto;
    texto.setFont(font);
    texto.setCharacterSize(48);
    texto.setPosition(50, 50);
    texto.setFillColor(sf::Color::White);

    // Botón para incrementar el contador
    sf::RectangleShape boton(sf::Vector2f(150, 50));
    boton.setFillColor(sf::Color::Green);
    boton.setPosition(50, 150);

    sf::Text textoBoton;
    textoBoton.setFont(font);
    textoBoton.setCharacterSize(24);
    textoBoton.setFillColor(sf::Color::White);
    textoBoton.setString("Aumentar");
    textoBoton.setPosition(60, 160);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cierre de ventana
            if (event.type == sf::Event::Closed)
                window.close();

            // Pulsación botón
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::FloatRect botonBounds = boton.getGlobalBounds();

                if (botonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                {
                    contador++;
                }
            }
        }

        texto.setString("Contador: " + std::to_string(contador));

        window.clear();
        window.draw(texto);
        window.draw(boton);
        window.draw(textoBoton);
        window.display();
    }

    return 0;
}
