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
        return boton.getGlobalBounds().contains(
            static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)
        );
    }

    void dibujar(sf::RenderWindow &window) {
        window.draw(boton);
        window.draw(texto);
    }
};

struct Botones {
    BotonConTexto aumentar;
    BotonConTexto reducir;
    BotonConTexto salir;

    void dibujar(sf::RenderWindow &w) {
        aumentar.dibujar(w);
        reducir.dibujar(w);
        salir.dibujar(w);
    }
};

// Crea un botón rectangular con texto
BotonConTexto crearBotonConTexto(
    std::string texto, sf::Color color, sf::Vector2i posicion, sf::Font &font
) {
    int x = posicion.x;
    int y = posicion.y;
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

// Incluye toda la lógica para procesar un evento
void procesarEvento(
    sf::Event evento, int &contador, sf::RenderWindow &ventana, Botones &botones
) {
    // Cierre de ventana
    if (evento.type == sf::Event::Closed)
        ventana.close();

    // Pulsación botón
    else if (evento.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);

        if (botones.aumentar.colisiona(mousePos)) {
            contador++;
        } else if (botones.reducir.colisiona(mousePos)) {
            contador--;
        } else if (botones.salir.colisiona(mousePos)) {
            ventana.close();
        }
    }
}

// Actualiza el interfaz gráfico
void actualizarIU(
    sf::RenderWindow &ventana, Botones &botones, sf::Text &textoContador,
    int contador
) {
    textoContador.setString("Contador: " + std::to_string(contador));
    ventana.clear();
    ventana.draw(textoContador);
    botones.dibujar(ventana);
    ventana.display();
}

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
        "Aumentar", sf::Color::Green, sf::Vector2i(250, primeraFila), font
    );
    auto botonReducir = crearBotonConTexto(
        "Reducir", sf::Color::Red, sf::Vector2i(50, primeraFila), font
    );
    auto botonSalir = crearBotonConTexto(
        "Salir", sf::Color::Blue, sf::Vector2i(150, segundaFila), font
    );

    Botones botones = {botonAumentar, botonReducir, botonSalir};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            procesarEvento(event, contador, window, botones);
        }
        actualizarIU(window, botones, textoContador, contador);
    }

    return 0;
}
