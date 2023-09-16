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
#include <vector>

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
    Reiniciando
};

struct Etiquetas {
    sf::Text texto_contador;
    sf::Text texto_pizzas_preparadas;
};

struct Estado {
    EstadoJuego actual = MostrandoInstrucciones;
    int contador_pizzas_servidas = 0;
    int contador_pizzas_preparadas = 0;
    int objetivo = 0;
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
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta("<Placeholder>", font, tamano);
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

struct Botones {

    BotonConTexto empezar;
    BotonConTexto despachar;
    BotonConTexto reiniciar;
    BotonConTexto salir;
    std::vector<BotonConTexto *> todos;

    // Crea todos los botones del juego
    // Se mostrarán o no dependiendo del Estado
    Botones(sf::Font &font, int pos_y_bajo_etiquetas) {
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
        empezar = botonEmpezar;
        despachar = botonDespachar;
        reiniciar = botonReiniciar;
        salir = botonSalir;
        todos = {&empezar, &despachar, &reiniciar, &salir};
        assert(todos.size() == 4);
    }
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
    auto pos_x = MARGEN_IZQ_ETIQUETAS;
    auto pos_y = prev_position + font.getLineSpacing(TAMANO_FUENTE_ETIQUETAS);
    etiqueta.setPosition(pos_x, pos_y);
    return etiqueta;
}

// Incluye toda la lógica para procesar un evento
void procesarEvento(
    sf::Event evento, sf::RenderWindow &ventana, Botones &botones,
    Reloj &reloj_espera_antes_de_resultado, Estado &estado
) {
    // Cierre de ventana
    if (evento.type == sf::Event::Closed)
        ventana.close();

    else if (evento.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, evento.size.width, evento.size.height);

        ventana.setView(sf::View(visibleArea));
    }

    // Pulsación botón
    else if (evento.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(ventana);

        // Fijos
        if (botones.salir.colisiona(mousePos)) {
            ventana.close();
        } else if (botones.reiniciar.colisiona(mousePos)) {
            estado.actual = Reiniciando;
            return;
        }
        // Dependientes del estado
        if (estado.actual == MostrandoInstrucciones) {
            auto bounds = botones.empezar.boton.getGlobalBounds();
            if (botones.empezar.colisiona(mousePos)) {
                estado.actual = Activo;
                botones.empezar.visible = false;
                botones.despachar.visible = true;
            }
        } else if (estado.actual == Activo) {
            if (botones.despachar.colisiona(mousePos)) {
                if (estado.contador_pizzas_preparadas > 0) {
                    estado.contador_pizzas_preparadas--;
                    estado.contador_pizzas_servidas++;
                    if (estado.contador_pizzas_servidas >= estado.objetivo) {
                        estado.actual = EsperaAntesDeResultado;
                        botones.despachar.visible = false;
                        reloj_espera_antes_de_resultado.start();
                    }
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
    etiquetas.texto_pizzas_preparadas.setString(
        "Pizzas preparadas: " +
        std::to_string(estado.contador_pizzas_preparadas)
    );
    ventana.clear();

    draw_grid(ventana, grid);

    for (auto boton_ptr : botones.todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->dibujar(ventana);
    }

    if (estado.actual == MostrandoInstrucciones) {
        ventana.draw(instrucciones);
    } else if (estado.actual == Activo || estado.actual == EsperaAntesDeResultado) {
        ventana.draw(etiquetas.texto_contador);
        ventana.draw(etiquetas.texto_pizzas_preparadas);
    } else {
        assert(estado.actual == MostrandoResultado);
        ventana.draw(resultado);
    }

    ventana.display();
}

sf::Text generar_instrucciones(
    sf::Font &font, std::string plantilla_instrucciones, int objetivo
) {
    auto etiqueta = crearEtiqueta(TAMANO_FUENTE_INFO, font, sf::Color::Yellow);
    etiqueta.setString(
        construir_instrucciones(plantilla_instrucciones, objetivo)
    );
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
    std::string instrucciones;
    int pizzas_preparadas_iniciales = 0;
    int objetivo_pizzas = 0;
};

/* Devuelve true si se debe pasar al siguiente nivel,
 * false para reiniciar
 */
bool nivel(                  //
    Globales &globales,      //
    Estado &estado,          //
    DatosNivel &datos_nivel, //
    Grid &grid,              //
    bool es_el_ultimo
) {
    estado.actual = MostrandoInstrucciones;
    estado.contador_pizzas_preparadas = datos_nivel.pizzas_preparadas_iniciales;
    estado.objetivo = datos_nivel.objetivo_pizzas;

    auto instrucciones = generar_instrucciones(
        globales.font, datos_nivel.instrucciones, estado.objetivo
    );
    auto resultado = generar_resultado(globales.font);

    // Etiquetas
    sf::Text last;
    sf::Text textoContador = crearEtiquetaContador(globales.font);
    Etiquetas etiquetas = {textoContador};

    auto prev_position = textoContador.getPosition().y;
    sf::Text etiquetaPizzasPreparadas =
        crearEtiquetaPizzasPreparadas(globales.font, prev_position);
    last = etiquetaPizzasPreparadas;
    etiquetas.texto_pizzas_preparadas = etiquetaPizzasPreparadas;

    sf::FloatRect bounds = last.getGlobalBounds();
    auto pos_y_bajo_etiquetas = bounds.top + bounds.height;

    // Botones
    Botones botones(globales.font, pos_y_bajo_etiquetas);

    botones.reiniciar.visible = true;
    botones.salir.visible = true;
    botones.empezar.visible = true;

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
            if (!es_el_ultimo) {
                float seconds = reloj_fin_nivel.get_seconds();
                if (seconds >= ESPERA_ENTRE_NIVELES) {
                    break;
                };
            }
        } else if (estado.actual == Reiniciando) {
            return false;
        }
        actualizarIU(
            globales.window, botones, etiquetas, instrucciones, resultado,
            estado, grid
        );
    }
    return true;
}

int juego() {
    Globales globales;
    Grid grid{};
    ResultadoSetup resultado_setup = setup_juego(globales);
    if (!resultado_setup.ok)
        return EXIT_FAILURE;

    DatosNivel datos[] = {
        {INSTRUCCIONES_NIVEL_1, 10, 10},
    };

    while (true) {
        bool reiniciar = false;
        for (int i = 0; i < std::size(datos); i++) {
            Estado estado = {};
            bool es_el_ultimo = (i == std::size(datos) - 1);
            bool res = nivel(globales, estado, datos[i], grid, es_el_ultimo);
            if (!res) {
                reiniciar = true;
                break;
            }
        }
        if (reiniciar) {
            continue;
        }
        break;
    }

    return 0;
}
