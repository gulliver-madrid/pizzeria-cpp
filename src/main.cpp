#include "manejo_rutas.h"
#include "paths.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <string>

#define TITLE "Pizzería"
#define FPS 30

#define A_ACUTE "\u00E1"
#define E_ACUTE "\u00E9"
#define I_ACUTE "\u00ED"
#define O_ACUTE "\u00F3"
#define U_ACUTE "\u00FA"
#define N_TILDE "\u00F1"
#define START_EXCLAMATION "\u00A1"
#define START_QUESTION "\u00BF"

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
    BotonConTexto despachar;
    BotonConTexto salir;

    void dibujar(sf::RenderWindow &w) {
        despachar.dibujar(w);
        salir.dibujar(w);
    }
};

sf::Text
crearEtiqueta(int tamano, sf::Font &font, sf::Color color = sf::Color::White) {
    sf::Text etiqueta;
    etiqueta.setFont(font);
    etiqueta.setCharacterSize(tamano);
    etiqueta.setFillColor(color);
    return etiqueta;
}

// Crea un botón rectangular con texto
BotonConTexto crearBotonConTexto(
    std::string texto, sf::Color color_fondo, sf::Vector2i posicion,
    sf::Font &font, sf::Color color_texto = sf::Color::White
) {
    int tamano_texto = 24;
    int x = posicion.x;
    int y = posicion.y;
    int margin = 10;
    // Rect
    sf::RectangleShape rect(sf::Vector2f(150, 50));
    rect.setFillColor(color_fondo);
    rect.setPosition(x, y);
    // Etiqueta
    sf::Text etiqueta = crearEtiqueta(tamano_texto, font, color_texto);
    etiqueta.setString(texto);
    etiqueta.setPosition(x + margin, y + margin);

    BotonConTexto boton = {rect, etiqueta};
    return boton;
};

// Crea la etiqueta de texto que mostrará el contador
sf::Text crearEtiquetaContador(sf::Font &font) {
    sf::Text etiqueta = crearEtiqueta(48, font, sf::Color::White);
    etiqueta.setPosition(50, 50);
    return etiqueta;
}

Botones crearBotones(sf::Font &font) {
    int primeraFila = 150;
    int segundaFila = 250;

    // Botones para incrementar o reducir el contador
    auto botonAumentar = crearBotonConTexto(
        "Despachar pizza", sf::Color::Green, sf::Vector2i(250, primeraFila),
        font, sf::Color::Black
    );

    auto botonSalir = crearBotonConTexto(
        "Salir", sf::Color::Blue, sf::Vector2i(150, segundaFila), font
    );

    Botones botones = {botonAumentar, botonSalir};
    return botones;
}

// Incluye toda la lógica para procesar un evento
void procesarEvento(
    sf::Event evento, int &contador, sf::RenderWindow &ventana,
    Botones &botones, BotonConTexto boton_empezar, bool &mostrando_instrucciones
) {
    // Cierre de ventana
    if (evento.type == sf::Event::Closed)
        ventana.close();

    // Pulsación botón
    else if (evento.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);
        if (mostrando_instrucciones) {
            if (boton_empezar.colisiona(mousePos)) {
                mostrando_instrucciones = false;
            }
        } else {
            if (botones.despachar.colisiona(mousePos)) {
                contador++;
            } else if (botones.salir.colisiona(mousePos)) {
                ventana.close();
            }
        }
    }
}

// Actualiza el interfaz gráfico
void actualizarIU(
    sf::RenderWindow &ventana, Botones &botones, sf::Text &textoContador,
    int contador, BotonConTexto boton_empezar, sf::Text instrucciones,
    bool mostrando_instrucciones
) {
    textoContador.setString("Clientes servidos: " + std::to_string(contador));
    ventana.clear();
    if (mostrando_instrucciones) {
        ventana.draw(instrucciones);
        boton_empezar.dibujar(ventana);
    } else {
        ventana.draw(textoContador);
        botones.dibujar(ventana);
    }
    ventana.display();
}

std::string construir_instrucciones() {
    std::ostringstream oss;
    oss << "Pizzer" << I_ACUTE
        << "a\nEl objetivo del juego es gestionar con exito tu "
           "pizzer"
        << I_ACUTE << "a.\n"
        << "Tu primera misi" << O_ACUTE
        << "n es conseguir 5 clientes satisfechos.\n"
        << START_EXCLAMATION << "Suerte!";
    return oss.str();
}

sf::Text generar_instrucciones(sf::Font &font) {
    auto etiqueta = crearEtiqueta(36, font, sf::Color::Yellow);
    etiqueta.setString(construir_instrucciones());
    etiqueta.setPosition(200, 200);
    return etiqueta;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 920), TITLE);
    window.setFramerateLimit(FPS);
    bool mostrando_instrucciones = true;

    // Fuente
    sf::Font font;
    if (!font.loadFromFile(getResourcePath(FONT_PATH).string())) {
        std::cout << "No se encontró ninguna fuente válida en \"" << FONT_PATH
                  << "\". Por favor, proporcione una fuente en esa ruta para "
                     "ejecutar el programa."
                  << std::endl;
        return EXIT_FAILURE;
    }

    auto instrucciones = generar_instrucciones(font);
    auto botonEmpezar = crearBotonConTexto(
        "Empezar", sf::Color::Green, sf::Vector2i(500, 450), font,
        sf::Color::Black
    );

    // Contador
    int contador_clientes = 0;

    sf::Text textoContador = crearEtiquetaContador(font);

    Botones botones = crearBotones(font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            procesarEvento(
                event, contador_clientes, window, botones, botonEmpezar,
                mostrando_instrucciones
            );
        }
        actualizarIU(
            window, botones, textoContador, contador_clientes, botonEmpezar,
            instrucciones, mostrando_instrucciones
        );
    }

    return 0;
}
