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

BotonConTexto crearBotonConTexto(
    std::string texto, sf::Color color, int x, int y, sf::Font &font
) {
    // Rect
    sf::RectangleShape rect(sf::Vector2f(150, 50));
    rect.setFillColor(color);
    rect.setPosition(x, y);
    // Etiqueta
    sf::Text etiqueta;
    etiqueta.setFont(font);
    etiqueta.setCharacterSize(24);
    etiqueta.setFillColor(sf::Color::White);
    etiqueta.setString(texto);
    etiqueta.setPosition(x + 10, y + 10);

    BotonConTexto boton = {rect, etiqueta};
    return boton;
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

    // Botones para incrementar o reducir el contador
    auto botonAumentar =
        crearBotonConTexto("Aumentar", sf::Color::Green, 250, 150, font);
    auto botonReducir =
        crearBotonConTexto("Reducir", sf::Color::Red, 50, 150, font);

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
