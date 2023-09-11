#include "cadenas.h"
#include "componentes.h"
#include "manejo_rutas.h"
#include "paths.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <chrono>
#include <iostream>
#include <optional>
#include <string>
#include <thread>

#define TITLE "Pizzer%ia"
#define FPS 12
#define RETARDO_ANTES_DE_RESULTADO 0.6

enum EstadoJuego {
    MostrandoInstrucciones,
    Activo,
    EsperaAntesDeResultado,
    MostrandoResultado,
};

struct Botones {
    BotonConTexto empezar;
    BotonConTexto despachar;
    BotonConTexto salir;
    BotonConTexto reiniciar;
};

struct Estado {
    EstadoJuego actual = MostrandoInstrucciones;
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
    int margin = 25;

    // Etiqueta
    sf::Text etiqueta = crearEtiqueta(tamano_texto, font, color_texto);
    etiqueta.setString(texto);
    etiqueta.setPosition(x + margin, y + margin);

    sf::FloatRect textRect = etiqueta.getGlobalBounds();
    // Rect
    sf::RectangleShape rect(
        sf::Vector2f(textRect.width + margin * 2, textRect.height + margin * 2)
    );
    rect.setFillColor(color_fondo);
    rect.setPosition(x, y);

    BotonConTexto boton = {rect, etiqueta};
    return boton;
};

// Crea la etiqueta de texto que mostrará el contador
sf::Text crearEtiquetaContador(sf::Font &font) {
    sf::Text etiqueta = crearEtiqueta(48, font, sf::Color::White);
    etiqueta.setPosition(50, 50);
    return etiqueta;
}

// Crea todos los botones del juego
// Se mostrarán o no dependiendo del Estado
Botones crearBotones(sf::Font &font) {
    int primeraFila = 150;
    int bottom = 800;

    auto botonEmpezar = crearBotonConTexto(
        "Empezar", sf::Color::Green, sf::Vector2i(500, 450), font,
        sf::Color::Black
    );
    auto botonAumentar = crearBotonConTexto(
        "Despachar pizza", sf::Color::Green, sf::Vector2i(250, primeraFila),
        font, sf::Color::Black
    );

    auto botonReiniciar = crearBotonConTexto(
        "Reiniciar", sf::Color::Blue, sf::Vector2i(150, bottom), font
    );
    auto botonSalir = crearBotonConTexto(
        "Salir", sf::Color::Red, sf::Vector2i(400, bottom), font
    );

    Botones botones = {botonEmpezar, botonAumentar, botonSalir, botonReiniciar};
    return botones;
}

// Incluye toda la lógica para procesar un evento
void procesarEvento(
    sf::Event evento, int &contador, sf::RenderWindow &ventana,
    Botones &botones, sf::Clock &clock, Estado &estado
) {
    // Cierre de ventana
    if (evento.type == sf::Event::Closed)
        ventana.close();

    // Pulsación botón
    else if (evento.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);

        // Fijos
        if (botones.salir.colisiona(mousePos)) {
            ventana.close();
        } else if (botones.reiniciar.colisiona(mousePos)) {
            contador = 0;
            estado.actual = MostrandoInstrucciones;
            return;
        }
        // Dependientes del estado
        if (estado.actual == MostrandoInstrucciones) {
            if (botones.empezar.colisiona(mousePos)) {
                estado.actual = Activo;
            }
        } else if (estado.actual == Activo) {
            if (botones.despachar.colisiona(mousePos)) {
                contador++;
                if (contador >= 5) {
                    estado.actual = EsperaAntesDeResultado;
                    clock.restart();
                }
            }
        }
    }
}

// Actualiza el interfaz gráfico
void actualizarIU(
    sf::RenderWindow &ventana, Botones &botones, sf::Text &textoContador,
    int contador, sf::Text instrucciones, sf::Text resultado, Estado &estado
) {
    textoContador.setString("Clientes servidos: " + std::to_string(contador));
    ventana.clear();
    if (estado.actual == MostrandoInstrucciones) {
        ventana.draw(instrucciones);
        botones.empezar.dibujar(ventana);
    } else if (estado.actual == Activo || estado.actual == EsperaAntesDeResultado) {
        ventana.draw(textoContador);
        botones.despachar.dibujar(ventana);
    } else {
        assert(estado.actual == MostrandoResultado);
        ventana.draw(resultado);
    }
    botones.reiniciar.dibujar(ventana);
    botones.salir.dibujar(ventana);
    ventana.display();
}

std::string construir_instrucciones() {
    std::string plantilla =
        "Pizzer%ia.\nEl objetivo del juego es gestionar con exito tu "
        "pizzer%ia.\nTu primera misi%on es conseguir 5 clientes "
        "satisfechos.\n%!Suerte!";
    return interpolar(plantilla);
}
std::string construir_resultado() {
    std::string plantilla =
        "%!Enhorabuena! Todos los clientes est%an satisfechos.";
    return interpolar(plantilla);
}

sf::Text generar_instrucciones(sf::Font &font) {
    auto etiqueta = crearEtiqueta(36, font, sf::Color::Yellow);
    etiqueta.setString(construir_instrucciones());
    etiqueta.setPosition(200, 200);
    return etiqueta;
}
sf::Text generar_resultado(sf::Font &font) {
    auto etiqueta = crearEtiqueta(36, font, sf::Color::Green);
    etiqueta.setString(construir_resultado());
    etiqueta.setPosition(200, 200);
    return etiqueta;
}

int main() {
    std::string title = TITLE;
    sf::RenderWindow window(sf::VideoMode(1800, 920), interpolar(title));
    window.setFramerateLimit(FPS);
    Estado estado;

    // Fuente
    sf::Font font;
    if (!font.loadFromFile(getResourcePath(FONT_PATH).string())) {
        std::cout << "No se encontró ninguna fuente válida en \"" << FONT_PATH
                  << "\". Por favor, proporcione una fuente en esa ruta para "
                     "ejecutar el programa."
                  << std::endl;
        return EXIT_FAILURE;
    }

    std::optional<sf::SoundBuffer> opt_buffer;
    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(getResourcePath(SUCCESS_SOUND_PATH).string()))
            opt_buffer = buffer;
    }

    auto instrucciones = generar_instrucciones(font);
    auto resultado = generar_resultado(font);

    int contador_clientes = 0;

    sf::Text textoContador = crearEtiquetaContador(font);

    Botones botones = crearBotones(font);

    sf::Clock clock;
    sf::Sound sound;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            procesarEvento(
                event, contador_clientes, window, botones, clock, estado
            );
        }
        if ( //
            estado.actual == EsperaAntesDeResultado &&
            clock.getElapsedTime().asSeconds() >= RETARDO_ANTES_DE_RESULTADO
        ) {
            estado.actual = MostrandoResultado;
            if (opt_buffer) {
                sound.setBuffer(opt_buffer.value());
                sound.play();
            }
        }
        actualizarIU(
            window, botones, textoContador, contador_clientes, instrucciones,
            resultado, estado
        );
    }

    return 0;
}
