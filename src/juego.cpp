#include "juego.h"
#include "cadenas.h"
#include "componentes.h"
#include "grid.h"
#include "manejo_rutas.h"
#include "paths.h"
#include "textos.h"
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
#define TAMANO_FUENTE_INFO 36
#define TAMANO_FUENTE_ETIQUETAS 48
#define MARGEN_IZQ_ETIQUETAS 50
#define TAMANO_INICIAL_VENTANA 1800, 920
#define FPS 12
#define RETARDO_ANTES_DE_RESULTADO 1
#define ESPERA_ENTRE_NIVELES 1.5

struct Globales {
    sf::RenderWindow window;
    sf::Font font;
    std::optional<sf::SoundBuffer> opt_buffer;
};

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

struct Etiquetas {
    sf::Text texto_contador;
    std::optional<sf::Text> texto_pizzas_preparadas = std::nullopt;
};

struct Estado {
    EstadoJuego actual = MostrandoInstrucciones;
    int contador_pizzas_servidas = 0;
    int contador_pizzas_preparadas = 0;
    int objetivo = 5;
};

struct Reloj {
  private:
    std::optional<sf::Clock> clock;

  public:
    void start() { //
        clock.emplace();
    }
    float get_seconds() {
        assert(clock.has_value());
        float seconds = clock.value().getElapsedTime().asSeconds();
        return seconds;
    }
};

sf::Text
crearEtiqueta(int tamano, sf::Font &font, sf::Color color = sf::Color::White) {
    sf::Text etiqueta;
    etiqueta.setFont(font);
    etiqueta.setCharacterSize(tamano);
    etiqueta.setFillColor(color);
    etiqueta.setString("<Placeholder>"); // Para poder obtener la altura
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

    // Primero creamos la etiqueta para usar sus límites en el Rect
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
    sf::Text etiqueta =
        crearEtiqueta(TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    etiqueta.setPosition(MARGEN_IZQ_ETIQUETAS, 50);
    return etiqueta;
}
sf::Text crearEtiquetaPizzasPreparadas(sf::Font &font, float prev_position) {
    sf::Text etiqueta =
        crearEtiqueta(TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    etiqueta.setPosition(
        MARGEN_IZQ_ETIQUETAS,
        prev_position + font.getLineSpacing(TAMANO_FUENTE_ETIQUETAS)
    );
    return etiqueta;
}

// Crea todos los botones del juego
// Se mostrarán o no dependiendo del Estado
Botones crearBotones(sf::Font &font, int pos_y_bajo_etiquetas) {
    int filaBotonesEjecutivos = pos_y_bajo_etiquetas + 50;
    int bottom = 800;

    auto botonEmpezar = crearBotonConTexto(
        "Empezar", sf::Color::Green, sf::Vector2i(500, 450), font,
        sf::Color::Black
    );
    auto botonDespachar = crearBotonConTexto(
        "Despachar pizza", sf::Color::Green,
        sf::Vector2i(250, filaBotonesEjecutivos), font, sf::Color::Black
    );

    auto botonReiniciar = crearBotonConTexto(
        "Reiniciar", sf::Color::Blue, sf::Vector2i(150, bottom), font
    );
    auto botonSalir = crearBotonConTexto(
        "Salir", sf::Color::Red, sf::Vector2i(400, bottom), font
    );

    Botones botones = {
        botonEmpezar, botonDespachar, botonSalir, botonReiniciar
    };
    return botones;
}

// Incluye toda la lógica para procesar un evento
void procesarEvento(
    sf::Event evento, sf::RenderWindow &ventana, Botones &botones,
    Reloj &reloj_espera_antes_de_resultado, Estado &estado
) {
    // Cierre de ventana
    if (evento.type == sf::Event::Closed)
        ventana.close();

    // Pulsación botón
    else if (evento.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);
        std::cout << "mousePos: " << mousePos.x << ", " << mousePos.y
                  << std::endl;

        // Fijos
        if (botones.salir.colisiona(mousePos)) {
            ventana.close();
        } else if (botones.reiniciar.colisiona(mousePos)) {
            estado.contador_pizzas_servidas = 0;
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
                estado.contador_pizzas_preparadas--;
                estado.contador_pizzas_servidas++;
                if (estado.contador_pizzas_servidas >= estado.objetivo) {
                    estado.actual = EsperaAntesDeResultado;
                    reloj_espera_antes_de_resultado.start();
                }
            }
        }
    }
}

/* Actualiza el interfaz gráfico */
void actualizarIU(             //
    sf::RenderWindow &ventana, //
    Botones &botones,          //
    Etiquetas &etiquetas,      //
    sf::Text instrucciones,    //
    sf::Text resultado,        //
    Estado &estado,            //
    Grid &grid
) {
    etiquetas.texto_contador.setString(
        "Clientes servidos: " + std::to_string(estado.contador_pizzas_servidas)
    );
    if (etiquetas.texto_pizzas_preparadas.has_value())
        etiquetas.texto_pizzas_preparadas.value().setString(
            "Pizzas preparadas: " +
            std::to_string(estado.contador_pizzas_preparadas)
        );
    ventana.clear();

    // Dibuja la cuadrícula con la textura almacenada
    draw_grid(ventana, grid);

    if (estado.actual == MostrandoInstrucciones) {
        ventana.draw(instrucciones);
        botones.empezar.dibujar(ventana);
    } else if (estado.actual == Activo || estado.actual == EsperaAntesDeResultado) {
        ventana.draw(etiquetas.texto_contador);
        if (etiquetas.texto_pizzas_preparadas.has_value()) {
            ventana.draw(etiquetas.texto_pizzas_preparadas.value());
        }
        if (estado.actual == Activo)
            botones.despachar.dibujar(ventana);
    } else {
        assert(estado.actual == MostrandoResultado);
        ventana.draw(resultado);
    }
    botones.reiniciar.dibujar(ventana);
    botones.salir.dibujar(ventana);
    ventana.display();
}

sf::Text
generar_instrucciones(sf::Font &font, std::string plantilla_instrucciones) {
    auto etiqueta = crearEtiqueta(TAMANO_FUENTE_INFO, font, sf::Color::Yellow);
    etiqueta.setString(construir_instrucciones(plantilla_instrucciones));
    etiqueta.setPosition(200, 200);
    return etiqueta;
}
sf::Text generar_resultado(sf::Font &font) {
    auto etiqueta = crearEtiqueta(TAMANO_FUENTE_INFO, font, sf::Color::Green);
    etiqueta.setString(construir_resultado());
    etiqueta.setPosition(200, 200);
    return etiqueta;
}
struct ResultadoSetup {
  private:
    ResultadoSetup(bool ok) : ok(ok) {}

  public:
    bool ok;

    static ResultadoSetup err() { return {false}; }
    ResultadoSetup() : ok(true) {}
};

// Inicia los elementos del juego que permanecerán entre niveles
// Inicializa las variables globales window, font y buffer
ResultadoSetup setup_juego(Globales &globales) {
    std::string title = TITLE;
    globales.window.create(
        sf::VideoMode(TAMANO_INICIAL_VENTANA), interpolar(title)
    );
    globales.window.setFramerateLimit(FPS);

    if (!globales.font.loadFromFile(getResourcePath(FONT_PATH).string()))
        return ResultadoSetup::err();

    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(getResourcePath(SUCCESS_SOUND_PATH).string()))
            globales.opt_buffer = buffer;
    }

    return ResultadoSetup();
}

struct DatosNivel {
    bool usar_pizzas_preparadas;
    std::string instrucciones;
    int pizzas_preparadas_iniciales = 0;
    int objetivo_pizzas = 5;
};

void nivel(                  //
    Globales &globales,      //
    Estado &estado,          //
    DatosNivel &datos_nivel, //
    Grid &grid
) {
    estado.actual = MostrandoInstrucciones;
    estado.contador_pizzas_preparadas = datos_nivel.pizzas_preparadas_iniciales;
    estado.objetivo = datos_nivel.objetivo_pizzas;

    auto instrucciones =
        generar_instrucciones(globales.font, datos_nivel.instrucciones);
    auto resultado = generar_resultado(globales.font);

    sf::Text last;
    sf::Text textoContador = crearEtiquetaContador(globales.font);
    Etiquetas etiquetas = {textoContador};
    last = textoContador;
    auto prev_position = textoContador.getPosition().y;
    if (datos_nivel.usar_pizzas_preparadas) {
        sf::Text etiquetaPizzasPreparadas =
            crearEtiquetaPizzasPreparadas(globales.font, prev_position);
        last = etiquetaPizzasPreparadas;
        etiquetas.texto_pizzas_preparadas = etiquetaPizzasPreparadas;
    }

    sf::FloatRect bounds = last.getGlobalBounds();
    auto pos_y_bajo_etiquetas = bounds.top + bounds.height;

    Botones botones = crearBotones(globales.font, pos_y_bajo_etiquetas);

    Reloj reloj_espera_antes_de_resultado;
    Reloj reloj_fin_nivel;
    sf::Sound sound;

    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            procesarEvento(
                event, globales.window, botones,
                reloj_espera_antes_de_resultado, estado
            );
        }
        if ( //
            estado.actual == EsperaAntesDeResultado &&
            reloj_espera_antes_de_resultado.get_seconds()>= RETARDO_ANTES_DE_RESULTADO
        ) {
            estado.actual = MostrandoResultado;
            if (globales.opt_buffer) {
                sound.setBuffer(globales.opt_buffer.value());
                sound.play();
            }
            reloj_fin_nivel.start();
        } else if (estado.actual == MostrandoResultado) {
            float seconds = reloj_fin_nivel.get_seconds();
            if (seconds >= ESPERA_ENTRE_NIVELES) {
                break;
            };
        }
        actualizarIU(
            globales.window, botones, etiquetas, instrucciones, resultado,
            estado, grid
        );
    }
}

int juego() {
    Globales globales;
    Grid grid{};
    ResultadoSetup resultado_setup = setup_juego(globales);
    if (!resultado_setup.ok)
        return EXIT_FAILURE;

    DatosNivel datos[] = {
        {false, INSTRUCCIONES_NIVEL_1},
        {true, INSTRUCCIONES_NIVEL_2, 10, 10},
    };
    for (int i = 0; i < std::size(datos); i++) {
        Estado estado = {};
        nivel(globales, estado, datos[i], grid);
    }

    return 0;
}
