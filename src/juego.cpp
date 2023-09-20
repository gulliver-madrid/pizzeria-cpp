#include "juego.h"
#include "cadenas.h"
#include "componentes.h"
#include "grid.h"
#include "manejo_rutas.h"
#include "paths.h"
#include "textos.h"
#include "tiempo.h"
#include "vista.h"
#include "vista_data.h"
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#define TITLE "Pizzer%ia"
#define TAMANO_FUENTE_INFO 36

namespace tiempos {
    const auto TIEMPO_PREPARACION = Tiempo::desde_segundos(2);
    const auto RETARDO_ANTES_DE_RESULTADO = Tiempo::desde_segundos(1);
    const auto ESPERA_ENTRE_NIVELES = Tiempo::desde_segundos(1.5);
} // namespace tiempos

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

struct EtiquetasContadores {
    sf::Text texto_contador;
    sf::Text texto_pizzas_preparadas;
};
struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

struct Estado {
    EstadoJuego actual = MostrandoInstrucciones;
    int contador_pizzas_servidas = 0;
    int contador_pizzas_preparadas = 0;
    int objetivo = 0;
    std::vector<TiempoPreparacion> encargadas = {};
};

// Incluye toda la lógica para procesar un evento
std::optional<EstadoJuego> procesarEvento(
    sf::Event evento, sf::RenderWindow &ventana, Botones &botones,
    Estado &estado
) {
    // Cierre de ventana
    if (evento.type == sf::Event::Closed)
        ventana.close();

    else if (evento.type == sf::Event::Resized) {
        // Actualiza la View al nuevo tamaño de la ventana
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
            return Reiniciando;
        }
        // Dependientes del estado
        if (estado.actual == MostrandoInstrucciones) {
            auto bounds = botones.empezar.boton.getGlobalBounds();
            if (botones.empezar.colisiona(mousePos)) {
                return Activo;
            }
        } else if (estado.actual == Activo) {
            if (botones.despachar.colisiona(mousePos) &&
                estado.contador_pizzas_preparadas > 0) {
                estado.contador_pizzas_preparadas--;
                estado.contador_pizzas_servidas++;

                if (estado.contador_pizzas_servidas >= estado.objetivo) {
                    return EsperaAntesDeResultado;
                }
            } else if (botones.encargar.colisiona(mousePos)) {
                auto total = tiempos::TIEMPO_PREPARACION;
                estado.encargadas.push_back(
                    TiempoPreparacion{obtener_tiempo_actual() + total, total}
                );
            }
        }
    }
    return std::nullopt;
};

/*
 * Actualiza el interfaz gráfico
 */
void actualizarIU(                   //
    sf::RenderWindow &ventana,       //
    Botones &botones,                //
    Paneles &paneles,                //
    TitulosPaneles &titulos_paneles, //
    EtiquetasContadores &contadores, //
    EtiquetasInfo &etiquetas_info,   //
    Estado &estado,                  //
    Grid &grid
) {
    contadores.texto_contador.setString(
        "Pizza Margarita: " + std::to_string(estado.contador_pizzas_servidas) +
        "/" + std::to_string(estado.objetivo)
    );
    contadores.texto_pizzas_preparadas.setString(
        "Pizza Margarita: " + std::to_string(estado.contador_pizzas_preparadas)
    );
    ventana.clear();
    if (DRAW_GRID)
        draw_grid(ventana, grid);

    paneles.dibujar(ventana);
    titulos_paneles.dibujar(ventana);

    // Update buttons state
    if (estado.contador_pizzas_preparadas == 0) {
        if (botones.despachar.activo)
            botones.despachar.activo = false;
    } else {
        if (!botones.despachar.activo)
            botones.despachar.activo = true;
    }
    if (estado.contador_pizzas_preparadas + estado.contador_pizzas_servidas +
            estado.encargadas.size() <
        estado.objetivo) {
        if (!botones.encargar.activo)
            botones.encargar.activo = true;
    } else {
        if (botones.encargar.activo)
            botones.encargar.activo = false;
    }

    for (auto boton_ptr : botones.todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->dibujar(ventana);
    }

    if (estado.actual == MostrandoInstrucciones) {
        ventana.draw(etiquetas_info.instrucciones);
    } else if (estado.actual == Activo || estado.actual == EsperaAntesDeResultado) {
        ventana.draw(contadores.texto_contador);
        ventana.draw(contadores.texto_pizzas_preparadas);
    } else {
        assert(estado.actual == MostrandoResultado);
        ventana.draw(etiquetas_info.resultado);
    }
    if (estado.actual == Activo) {
        std::vector<int> porcentajes;
        for (auto &tp : estado.encargadas) {
            porcentajes.push_back(tp.obtener_porcentaje());
        }
        auto porcentajes_visuales =
            crear_visualizaciones_porcentajes(porcentajes);
        // std::cout << "hay " << porcentajes_visuales.size() << "
        // visualizaciones"
        //           << std::endl;
        paneles.porcentajes_visuales = porcentajes_visuales;
        int i = 0;
        for (auto &tpv : paneles.porcentajes_visuales) {
            // std::cout << "Creando visualizacion de los tiempos de
            // preparación: "
            //           << i << std::endl;
            ventana.draw(tpv.fondo);
            ventana.draw(tpv.relleno);
            i++;
        }
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
        sf::VideoMode(TAMANO_INICIAL_VENTANA), interpolar_unicode(title)
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
    DatosNivel(std::string instr, int pizzas_iniciales, int obj_pizzas)
        : instrucciones(instr), pizzas_preparadas_iniciales(pizzas_iniciales),
          objetivo_pizzas(obj_pizzas) {}
};

void TitulosPaneles::dibujar(sf::RenderWindow &window) {
    if (visible) {
        window.draw(en_preparacion);
        window.draw(preparadas);
        window.draw(pedidos);
    }
}

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
    // Iniciamos el estado
    estado.actual = MostrandoInstrucciones;
    estado.contador_pizzas_preparadas = datos_nivel.pizzas_preparadas_iniciales;
    estado.objetivo = datos_nivel.objetivo_pizzas;

    auto instrucciones = generar_instrucciones(
        globales.font, datos_nivel.instrucciones, estado.objetivo
    );
    auto resultado = generar_resultado(globales.font);

    EtiquetasInfo etiquetas_info = {instrucciones, resultado};

    Paneles paneles;

    // Títulos paneles
    sf::Text titulo_1 = crearEtiquetaTituloPanel(
        globales.font, IndicePanel::PANEL_EN_PREPARACION, "En preparaci%on"
    );
    sf::Text titulo_2 = crearEtiquetaTituloPanel(
        globales.font, IndicePanel::PANEL_PREPARADAS, "Preparadas"
    );
    sf::Text titulo_3 = crearEtiquetaTituloPanel(
        globales.font, IndicePanel::PANEL_PEDIDOS, "Pedidos"
    );
    TitulosPaneles titulos_paneles = {titulo_1, titulo_2, titulo_3};

    // Contadores
    sf::Text textoContador = crearEtiquetaContador(globales.font);
    EtiquetasContadores contadores = {textoContador};

    contadores.texto_pizzas_preparadas =
        crearEtiquetaPizzasPreparadas(globales.font);

    // Botones
    Botones botones(globales.font);

    // Mostrar botones iniciales
    botones.reiniciar.visible = true;
    botones.salir.visible = true;
    botones.empezar.visible = true;

    Timer timer_espera_antes_de_resultado;
    Timer timer_fin_nivel;
    sf::Sound sound;
    int frame = 0;

    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            auto nuevo_estado =
                procesarEvento(event, globales.window, botones, estado);

            // Cambio de estado reciente
            if (nuevo_estado.has_value()) {
                switch (nuevo_estado.value()) {
                    case Activo:
                        assert(estado.actual == MostrandoInstrucciones);
                        botones.empezar.visible = false;
                        botones.despachar.visible = true;
                        botones.encargar.visible = true;
                        paneles.visible = true;
                        titulos_paneles.visible = true;
                        break;
                    case EsperaAntesDeResultado:
                        assert(estado.actual == Activo);
                        botones.despachar.visible = false;
                        botones.encargar.visible = false;
                        timer_espera_antes_de_resultado.start(
                            tiempos::RETARDO_ANTES_DE_RESULTADO
                        );
                        break;

                    case Reiniciando:
                        return false;
                }
                estado.actual = nuevo_estado.value();
            }
        }

        auto tiempo_actual = obtener_tiempo_actual();
        std::vector<TiempoPreparacion> restantes = {};
        for (size_t i = 0; i < estado.encargadas.size(); i++) {
            auto elem = estado.encargadas[i];
            if (tiempo_actual < elem.finalizacion) {
                restantes.push_back(elem);
            }
        }
        int listas = estado.encargadas.size() - restantes.size();
        estado.encargadas = std::move(restantes);
        estado.contador_pizzas_preparadas += listas;

        // En función del estado (no necesariamente reciente)
        switch (estado.actual) {
            case EsperaAntesDeResultado:
                if (timer_espera_antes_de_resultado.termino()) {
                    estado.actual = MostrandoResultado;
                    if (globales.opt_buffer) {
                        sound.setBuffer(globales.opt_buffer.value());
                        sound.play();
                    }
                    timer_fin_nivel.start(tiempos::ESPERA_ENTRE_NIVELES);
                    paneles.visible = false;
                    titulos_paneles.visible = false;
                }
                break;
            case MostrandoResultado: {
                if (!es_el_ultimo && timer_fin_nivel.termino()) {
                    return true;
                };
                break;
            }
        }

        actualizarIU(
            globales.window, botones, paneles, titulos_paneles, contadores,
            etiquetas_info, estado, grid
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
        {INSTRUCCIONES_NIVEL_1, 4, 6},
        {INSTRUCCIONES_NIVEL_2, 2, 6},
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
