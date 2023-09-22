#include "juego.h"
#include "botones.h"
#include "cadenas.h"
#include "dominio.h"
#include "grid.h"
#include "manejo_rutas.h"
#include "modelo.h"
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
#define TAMANO_FUENTE_RESULTADO 48

#define MAXIMO_PIZZAS_EN_PREPARACION 3
#define MAXIMO_PIZZAS_PREPARADAS 4

namespace colores {
    const auto COLOR_FONDO = sf::Color(60, 0, 150);
    const auto COLOR_TEXTO_INSTRUCCIONES = sf::Color::Yellow;
    const auto COLOR_TEXTO_RESULTADO = sf::Color(255, 160, 0);
} // namespace colores

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = Tiempo::desde_segundos(2.5);
    const auto ESPERA_ENTRE_NIVELES = Tiempo::desde_segundos(2);
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
    Reiniciando,
};

struct EtiquetasContadores {
    std::map<TipoPizza, sf::Text> texto_contador;
    std::map<TipoPizza, sf::Text> texto_pizzas_preparadas;
};

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
    int objetivo = 0;
};

struct EncargoACocina {
    TipoPizza tipo;
    TiempoPreparacion tiempo_preparacion;
};

struct Estado {
    EstadoJuego actual = MostrandoInstrucciones;
    std::map<TipoPizza, Contadores> contadores;
    std::vector<EncargoACocina> encargadas = {};
};

int encargadas_del_tipo(
    std::vector<EncargoACocina> &encargadas, TipoPizza tipo
) {
    int c = 0;
    for (auto &encargo : encargadas) {
        if (encargo.tipo == tipo) {
            c++;
        }
    }
    return c;
}

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
            for (auto &par : botones.despachar) {
                auto boton = par.second;
                auto &contador = estado.contadores[par.first];
                if (boton.colisiona(mousePos) && contador.preparadas > 0) {
                    contador.preparadas--;
                    contador.servidas++;
                }
            }
            bool faltan = false;
            for (auto tp : tipos_de_pizza) {
                if (estado.contadores[tp].servidas <
                    estado.contadores[tp].objetivo) {
                    faltan = true;
                    break;
                }
            }
            if (!faltan) {
                return EsperaAntesDeResultado;
            }
            for (auto &tp : tipos_de_pizza) {
                if (botones.encargar[tp].colisiona(mousePos)) {
                    auto total =
                        Tiempo::desde_segundos(tiempos_preparacion[tp]);
                    EncargoACocina encargo{
                        tp, //
                        TiempoPreparacion{
                            obtener_tiempo_actual() + total, total //
                        }
                    };
                    estado.encargadas.push_back(encargo);
                }
            }
        }
    }
    return std::nullopt;
};

/*
 * Actualiza el interfaz gráfico
 */
void actualizarIU(                       //
    sf::RenderWindow &ventana,           //
    Botones &botones,                    //
    PanelesCompletos &paneles_completos, //
    EtiquetasContadores &contadores,     //
    EtiquetasInfo &etiquetas_info,       //
    Estado &estado,                      //
    Grid &grid,                          //
    sf::Font font                        //
) {
    for (auto tp : tipos_de_pizza) {
        contadores.texto_contador[tp].setString(
            tipo_pizza_to_string[tp] + ": " +
            std::to_string(estado.contadores[tp].servidas) + "/" +
            std::to_string(estado.contadores[tp].objetivo)
        );
    }
    for (auto tp : tipos_de_pizza) {
        contadores.texto_pizzas_preparadas[tp].setString(
            tipo_pizza_to_string[tp] + ": " +
            std::to_string(estado.contadores[tp].preparadas)
        );
    }

    // Actualiza el estado de los botones
    for (auto tp : tipos_de_pizza) {
        auto &boton_despachar = botones.despachar[tp];
        if (estado.contadores[tp].preparadas == 0) {
            boton_despachar.desactivar();

        } else {
            boton_despachar.activar();
        }
    }
    int total_en_preparacion = estado.encargadas.size();

    for (auto &tp : tipos_de_pizza) {
        auto &boton_encargar = botones.encargar[tp];
        if (total_en_preparacion == MAXIMO_PIZZAS_EN_PREPARACION) {
            boton_encargar.desactivar();
            continue;
        } else {
            boton_encargar.activar();
        }
        auto contadores = estado.contadores[tp];
        int potenciales = contadores.preparadas + contadores.servidas +
                          encargadas_del_tipo(estado.encargadas, tp);
        if (potenciales < contadores.objetivo) {
            boton_encargar.activar();
        } else {
            boton_encargar.desactivar();
        }
    }

    // Limpia la ventana y empieza a pintar los componentes visuales
    ventana.clear(colores::COLOR_FONDO);
    if (DRAW_GRID)
        draw_grid(ventana, grid, GRID_SIZE, GRID_TONE);

    // Paneles
    if (estado.actual == Activo || estado.actual == EsperaAntesDeResultado) {
        std::vector<PorcentajeConTipoPizza> porcentajes;
        for (auto &encargo : estado.encargadas) {
            porcentajes.push_back(PorcentajeConTipoPizza{
                encargo.tiempo_preparacion.obtener_porcentaje(), encargo.tipo
            });
        }
        paneles_completos.dibujar(ventana, porcentajes, font);
    }

    // Textos
    switch (estado.actual) {
        case MostrandoInstrucciones:
            ventana.draw(etiquetas_info.instrucciones);
            break;
        case Activo:
        case EsperaAntesDeResultado:
            for (auto &tp : tipos_de_pizza) {
                ventana.draw(contadores.texto_contador[tp]);
                ventana.draw(contadores.texto_pizzas_preparadas[tp]);
            }
            break;

        default:
            assert(estado.actual == MostrandoResultado);
            ventana.draw(etiquetas_info.resultado);
            break;
    }

    botones.dibujar(ventana);

    ventana.display();
}

sf::Text generar_instrucciones(
    sf::Font &font, std::string plantilla_instrucciones, int objetivo
) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_INFO, font, colores::COLOR_TEXTO_INSTRUCCIONES
    );
    etiqueta.setString(
        construir_instrucciones(plantilla_instrucciones, objetivo)
    );
    etiqueta.setPosition(200, 200);
    return etiqueta;
}

sf::Text generar_resultado(sf::Font &font) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_RESULTADO, font, colores::COLOR_TEXTO_RESULTADO
    );
    etiqueta.setString(construir_resultado());
    etiqueta.setPosition(200, 200);
    return etiqueta;
}

/*
 * Evalua si hay pizzas ya preparadas y modifica el estado en consecuencia
 * maximo es el maximo de pizzas que podrán pasar
 * Las pizzas que lleven más tiempo preparadas pasan antes
 */
void evaluar_preparacion(Estado &estado, int maximo) {
    auto tiempo_actual = obtener_tiempo_actual();

    std::vector<std::pair<size_t, int>> listas_con_indice = {};
    // Primero hago una ronda paro saber cuales son las ya hechas
    for (size_t i = 0; i < estado.encargadas.size(); i++) {
        auto encargo = estado.encargadas[i];
        if ( //
            tiempo_actual >= encargo.tiempo_preparacion.finalizacion
        ) {
            // Exceso de tiempo que lleva preparada
            Tiempo diff =
                (tiempo_actual - encargo.tiempo_preparacion.finalizacion);
            listas_con_indice.push_back({i, diff.obtener_milisegundos()});
        }
    }

    if (listas_con_indice.size() > maximo) {
        // Ordenamos la lista de manera descendente
        // Las que llevan más tiempo preparadas salen antes
        std::sort(
            listas_con_indice.begin(), listas_con_indice.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; }
        );
        listas_con_indice.resize(maximo);
    }

    // Nos quedamos solo con los indices de las pizzas que pasan
    std::vector<size_t> pasan;
    for (const auto &par : listas_con_indice) {
        pasan.push_back(par.first);
    }

    std::vector<EncargoACocina> restantes = {};

    // Segunda ronda
    for (size_t i = 0; i < estado.encargadas.size(); i++) {
        auto encargo = estado.encargadas[i];
        auto it = std::find(pasan.begin(), pasan.end(), i);
        if (it != pasan.end()) {
            // Se encontro
            estado.contadores[encargo.tipo].preparadas++;
        } else {
            restantes.push_back(encargo);
        }
    }
    estado.encargadas = std::move(restantes);
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

struct DatosNivelTipoPizza {
    TipoPizza tipo;
    int pizzas_preparadas_iniciales = 0;
    int objetivo_pizzas = 0;
};

struct DatosNivel {
    std::string instrucciones;
    std::map<TipoPizza, DatosNivelTipoPizza> pizzas;
    DatosNivel(
        std::string instr, std::map<TipoPizza, DatosNivelTipoPizza> pizzas
    )
        : instrucciones(instr), pizzas(pizzas) {}
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
    // Iniciamos el estado
    estado.actual = MostrandoInstrucciones;
    for (auto tp : tipos_de_pizza) {
        estado.contadores[tp].preparadas =
            datos_nivel.pizzas[tp].pizzas_preparadas_iniciales;
        estado.contadores[tp].objetivo = datos_nivel.pizzas[tp].objetivo_pizzas;
    }
    int total = 0;
    for (auto tp : tipos_de_pizza) {
        total += estado.contadores[tp].objetivo;
    }
    auto instrucciones =
        generar_instrucciones(globales.font, datos_nivel.instrucciones, total);
    auto resultado = generar_resultado(globales.font);

    EtiquetasInfo etiquetas_info = {instrucciones, resultado};

    PanelesCompletos paneles_completos(globales.font);
    EtiquetasContadores contadores;
    // Contadores
    int i = 0;
    for (auto tp : tipos_de_pizza) {
        contadores.texto_contador[tp] = crearEtiquetaContador(globales.font, i);
        contadores.texto_pizzas_preparadas[tp] =
            crearEtiquetaPizzasPreparadas(globales.font, i);
        i++;
    }

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
                        for (auto tp : tipos_de_pizza) {
                            botones.despachar[tp].visible = true;
                            botones.encargar[tp].visible = true;
                        }
                        paneles_completos.visible = true;
                        break;
                    case EsperaAntesDeResultado:
                        assert(estado.actual == Activo);
                        for (auto tp : tipos_de_pizza) {
                            botones.despachar[tp].visible = false;
                            botones.encargar[tp].visible = false;
                        }
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

        int total_preparadas = 0;
        for (auto tp : tipos_de_pizza) {
            total_preparadas += estado.contadores[tp].preparadas;
        }

        if (total_preparadas < MAXIMO_PIZZAS_PREPARADAS) {
            int maximo = MAXIMO_PIZZAS_PREPARADAS - total_preparadas;
            evaluar_preparacion(estado, maximo);
        }

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
                    paneles_completos.visible = false;
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
            globales.window, botones, paneles_completos, contadores,
            etiquetas_info, estado, grid, globales.font
        );
    }
    return true;
}

int juego() {
    Globales globales;
    Grid grid;
    ResultadoSetup resultado_setup = setup_juego(globales);
    if (!resultado_setup.ok)
        return EXIT_FAILURE;

    DatosNivel datos[] = {
        {INSTRUCCIONES_NIVEL_1,
         {
             {
                 Margarita,
                 DatosNivelTipoPizza{Margarita, 2, 8},
             },
             {
                 Pepperoni,
                 DatosNivelTipoPizza{Pepperoni, 0, 4},
             },
             {
                 CuatroQuesos,
                 DatosNivelTipoPizza{CuatroQuesos, 0, 3},
             },
         }},
        {INSTRUCCIONES_NIVEL_2,
         {
             {
                 Margarita,
                 DatosNivelTipoPizza{Margarita, 2, 6},
             },
             {
                 Pepperoni,
                 DatosNivelTipoPizza{Pepperoni, 1, 3},
             },
             {
                 CuatroQuesos,
                 DatosNivelTipoPizza{CuatroQuesos, 0, 6},
             },
         }},
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
