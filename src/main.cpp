#include "manejo_rutas.h"
#include "paths.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

struct BotonConTexto {
    sf::RectangleShape boton;
    sf::Text texto;
};

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
    sf::RectangleShape rectBotonReducir(sf::Vector2f(150, 50));
    rectBotonReducir.setFillColor(sf::Color::Red);
    rectBotonReducir.setPosition(50, 150);

    // Botón para incrementar el contador
    sf::RectangleShape rectBotonAumentar(sf::Vector2f(150, 50));
    rectBotonAumentar.setFillColor(sf::Color::Green);
    rectBotonAumentar.setPosition(250, 150);

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

    BotonConTexto botonAumentar = {rectBotonAumentar, textoBotonAumentar};
    BotonConTexto botonReducir = {rectBotonReducir, textoBotonReducir};

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
                    botonAumentar.boton.getGlobalBounds();
                sf::FloatRect botonReducirBounds =
                    botonReducir.boton.getGlobalBounds();

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
        window.draw(botonAumentar.boton);
        window.draw(botonAumentar.texto);
        window.draw(botonReducir.boton);
        window.draw(botonReducir.texto);
        window.display();
    }

    return 0;
}
