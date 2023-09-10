#include "manejo_rutas.h"
#include "paths.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

#define TITLE "Pizzería"

struct BotonConTexto {
    sf::RectangleShape boton;
    sf::Text texto;

    bool colisiona(sf::Vector2i &mousePos) {
        sf::FloatRect bounds = boton.getGlobalBounds();

        if (bounds.contains(
                static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)
            )) {
            return true;
        }
        return false;
    }

    void dibujar(sf::RenderWindow &window) {
        window.draw(boton);
        window.draw(texto);
    }
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
    sf::RenderWindow window(sf::VideoMode(1800, 920), TITLE);
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
    sf::Text textoContador;
    textoContador.setFont(font);
    textoContador.setCharacterSize(48);
    textoContador.setPosition(50, 50);
    textoContador.setFillColor(sf::Color::White);

    int primeraFila = 150;
    int segundaFila = 250;

    // Botones para incrementar o reducir el contador
    auto botonAumentar = crearBotonConTexto(
        "Aumentar", sf::Color::Green, 250, primeraFila, font
    );
    auto botonReducir =
        crearBotonConTexto("Reducir", sf::Color::Red, 50, primeraFila, font);
    auto botonSalir =
        crearBotonConTexto("Salir", sf::Color::Blue, 150, segundaFila, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cierre de ventana
            if (event.type == sf::Event::Closed)
                window.close();

            // Pulsación botón
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (botonAumentar.colisiona(mousePos)) {
                    contador++;
                } else if (botonReducir.colisiona(mousePos)) {
                    contador--;
                } else if (botonSalir.colisiona(mousePos)) {
                    window.close();
                }
            }
        }

        textoContador.setString("Contador: " + std::to_string(contador));

        window.clear();
        window.draw(textoContador);
        botonAumentar.dibujar(window);
        botonReducir.dibujar(window);
        botonSalir.dibujar(window);
        window.display();
    }

    return 0;
}
