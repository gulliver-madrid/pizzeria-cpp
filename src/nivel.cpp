#include "nivel.h"
#include "comandos.h"
#include "estado_nivel.h"
#include "tiempo.h"
#include "vista/enlace_vista.h"
#include "vista/vista.h"
#include <SFML/Window.hpp>
#include <cassert>
#include <functional>
#include <memory>

struct Realizador {
    using NuevaFase = std::optional<FaseNivel>;
    Estado &estado;
    /* Encarga una pizza a la cocina del tipo indicado */
    NuevaFase encargar_pizza( //
        const modelo::TipoPizza tp
    ) {
        assert(estado.fase_actual == FaseNivel::Activa);
        auto encargo = EncargoACocina( //
            tp, GestorTiempoJuego::obtener_tiempo_juego()
        );
        estado.encargos.anadir(encargo);
        return std::nullopt;
    }

    /*
     * Despacha una pizza a losclientes del tipo indicado. Devuelve la nueva
     * fase si corresponde.
     */
    NuevaFase despachar_pizza( //
        const modelo::TipoPizza tp
    ) {
        assert(estado.fase_actual == FaseNivel::Activa);
        estado.control_pizzas.procesar_despacho(tp);
        if (!estado.control_pizzas.faltan_pedidos_por_cubrir()) {
            return FaseNivel::EsperaAntesDeResultado;
        }
        return std::nullopt;
    }
    NuevaFase alternar_grid() {
        assert(MODO_DESARROLLO);
        estado.mostrando_grid = !estado.mostrando_grid;
        return std::nullopt;
    }
    NuevaFase empezar() {
        assert(estado.fase_actual == FaseNivel::MostrandoInstrucciones);
        return FaseNivel::Activa;
    }
};

struct ControladorClicks {
  private:
    std::optional<Comando> ControladorClicks::genera_comando(
        const std::function<bool(const BotonConTexto &boton)> &pulsado, //
        const BotonesApp &,                                             //
        const FaseNivel fase_actual                                     //
    );
    std::optional<FaseNivel> aplica_comando( //
        Estado &estado,                      //
        const Comando &comando
    );

  public:
    std::optional<FaseNivel> procesa_click(
        Globales &,                   //
        const BotonesApp &,           //
        Estado &,                     //
        const sf::Vector2i &mouse_pos //
    );
};

Nivel::Nivel(
    Globales &globales,            //
    const DatosNivel &datos_nivel, //
    const NumNivel &num_nivel,     //
    Grid &grid,                    //
    bool es_el_ultimo              //
)
    : globales(globales), datos_nivel(datos_nivel), num_nivel(num_nivel),
      grid(grid), es_el_ultimo(es_el_ultimo) {
    controlador_clicks = std::shared_ptr<ControladorClicks>();
}

/*
 * Incluye toda la lógica para procesar un evento. Devuelve la nueva fase,
 * en caso de que debiera cambiar.
 */
std::optional<FaseNivel> Nivel::procesarEvento(
    sf::Event evento, const BotonesApp &botones, Estado &estado
) {
    auto &ventana = globales.window;
    std::optional<FaseNivel> siguiente_fase;
    switch (evento.type) {
        case sf::Event::Closed:
            ventana.close();
            siguiente_fase = FaseNivel::Saliendo;
            break;
        case sf::Event::Resized:
            {
                // Actualiza la View al nuevo tamaño de la ventana
                sf::FloatRect visibleArea(
                    0, 0, evento.size.width, evento.size.height
                );
                ventana.setView(sf::View(visibleArea));
            }
            break;
        case sf::Event::MouseButtonPressed:
            {
                const sf::Vector2i mouse_pos = sf::Mouse::getPosition(ventana);
                siguiente_fase = controlador_clicks->procesa_click(
                    globales, botones, estado, mouse_pos
                );
            }
            break;
        default:
            /* Eventos ignorados */
            break;
    }
    return siguiente_fase;
};

std::optional<Comando> ControladorClicks::genera_comando(
    const std::function<bool(const BotonConTexto &boton)> &pulsado, //
    const BotonesApp &botones,                                      //
    const FaseNivel fase_actual                                     //
) {
    // Fijos
    if (pulsado(botones.generales.salir)) {
        return Comando::Salir{};
    } else if (pulsado(botones.generales.reiniciar)) {
        return Comando::Reiniciar{};
    } else if (pulsado(botones.generales.alternar_grid)) {
        return Comando::AlternarGrid{};
    }
    // Dependientes de la fase
    switch (fase_actual) {
        case FaseNivel::MostrandoInstrucciones:
            if (pulsado(botones.empezar)) {
                return Comando::Empezar{};
            }
            break;
        case FaseNivel::Activa:
            for (const auto &[tp, boton] : botones.encargar) {
                if (pulsado(boton)) {
                    return Comando::Encargar{tp};
                }
            }
            for (const auto &[tp, boton] : botones.despachar) {
                if (pulsado(boton)) {
                    return Comando::Despachar{tp};
                }
            }
            break;
        default:
            break;
    }
    return std::nullopt;
}

#define SWITCH(variante)                                                       \
    using T = std::decay_t<decltype(variante)>;                                \
    if (false) { /* Para inicializar los bloques if else */                    \
    }
#define CASE(comando, accion)                                                  \
    else if constexpr (std::is_same_v<T, Comando::comando>) {                  \
        return accion;                                                         \
    }
/* Aplica un comando y devuelve la nueva fase, si correspondiera cambiar */
std::optional<FaseNivel> ControladorClicks::aplica_comando( //
    Estado &estado,                                         //
    const Comando &comando                                  //

) {
    return std::visit(
        [&estado](auto &&variante) -> std::optional<FaseNivel> {
            Realizador realizador{estado};
            SWITCH(variante)
            CASE(Empezar, realizador.empezar())
            CASE(Salir, FaseNivel::Saliendo)
            CASE(Reiniciar, FaseNivel::Reiniciando)
            CASE(AlternarGrid, realizador.alternar_grid())
            CASE(Encargar, realizador.encargar_pizza(variante.tp))
            CASE(Despachar, realizador.despachar_pizza(variante.tp))
            return std::nullopt;
        },
        comando.variante
    );
}
#undef SWITCH
#undef CASE

std::optional<FaseNivel> ControladorClicks::procesa_click(
    Globales &globales,           //
    const BotonesApp &botones,    //
    Estado &estado,               //
    const sf::Vector2i &mouse_pos //

) {
    const auto pulsado = [&globales, &mouse_pos](const BotonConTexto &boton) {
        return globales.detecta_colision(boton, mouse_pos);
    };
    std::optional<Comando> comando = genera_comando( //
        pulsado, botones, estado.fase_actual
    );
    if (!comando) {
        return std::nullopt;
    }
    return aplica_comando(estado, comando.value());
}

/* Procesa un cambio de fase reciente */
std::optional<AccionGeneral> Nivel::procesa_cambio_de_fase(
    FaseNivel nueva_fase,                   //
    const EnlaceVista &enlace_vista,        //
    Timer &timer_espera_antes_de_resultado, //
    FaseNivel fase_previa                   //
) {
    std::optional<AccionGeneral> posible_accion;
    switch (nueva_fase) {
        case FaseNivel::Activa:
            assert(fase_previa == FaseNivel::MostrandoInstrucciones);
            GestorTiempoJuego::activar();
            enlace_vista.on_cambio_a_fase_activa();
            break;
        case FaseNivel::EsperaAntesDeResultado:
            assert(fase_previa == FaseNivel::Activa);
            GestorTiempoJuego::pausar();
            timer_espera_antes_de_resultado.start(
                tiempos::RETARDO_ANTES_DE_RESULTADO
            );
            enlace_vista.on_cambio_a_fase_espera_antes_de_resultado();
            break;
        case FaseNivel::Reiniciando:
            posible_accion = AccionGeneral::Reiniciar;
            break;
        case FaseNivel::Saliendo:
            posible_accion = AccionGeneral::Salir;
            break;
        default:
            assert(false);
            break;
    }
    return posible_accion;
}

void mostrar_resultado(
    const Globales &globales,        //
    Estado &estado,                  //
    const EnlaceVista &enlace_vista, //
    Timer &timer_fin_nivel,          //
    sf::Sound &sound                 //
) {
    // Pasa a fase MostrandoResultado
    estado.fase_actual = FaseNivel::MostrandoResultado;
    if (globales.success_buffer) {
        sound.setBuffer(globales.success_buffer.value());
        sound.play();
    }
    timer_fin_nivel.start(tiempos::ESPERA_ENTRE_NIVELES);
    enlace_vista.esconder_paneles();
}

EnlaceVista Nivel::crear_enlace_vista(
    const modelo::ControlPizzas &control_pizzas, //
    std::optional<int> objetivo_estatico         //
) {
    const auto vista_ptr = std::make_shared<Vista>(
        datos_nivel.es_estatico,               //
        globales.font,                         //
        grid,                                  //
        control_pizzas.get_tipos_disponibles() //
    );
    vista_ptr->setup(
        datos_nivel.instrucciones, //
        num_nivel,                 //
        objetivo_estatico          //
    );
    return EnlaceVista(vista_ptr);
}

AccionGeneral Nivel::ejecutar() {
    std::optional<int> objetivo_estatico; // Solo se define en estaticos
    modelo::ControlPizzas control_pizzas = {
        datos_nivel.pedidos, datos_nivel.es_estatico
    };
    Estado estado(FaseNivel::MostrandoInstrucciones, control_pizzas);
    assert(estado.establecido);
    modelo::PizzasAContadores &contadores = control_pizzas.contadores;
    if (datos_nivel.es_estatico.valor) {
        objetivo_estatico = control_pizzas.obtener_objetivo_total_estatico();
    }

    const auto enlace_vista = crear_enlace_vista( //
        control_pizzas, objetivo_estatico
    );

    Timer timer_espera_antes_de_resultado;
    Timer timer_fin_nivel;
    sf::Sound sound;
    GestorTiempoJuego::reiniciar();
    assert(!contadores.empty());

    while (globales.window.isOpen()) {
        sf::Event event;
        while (globales.window.pollEvent(event)) {
            auto siguiente_fase =
                procesarEvento(event, enlace_vista.vista->botones, estado);
            // Cambio de fase reciente
            if (!siguiente_fase.has_value()) {
                continue;
            }
            const auto fase_previa = estado.fase_actual;
            estado.fase_actual = siguiente_fase.value();
            const auto accion = procesa_cambio_de_fase(
                estado.fase_actual,              //
                enlace_vista,                    //
                timer_espera_antes_de_resultado, //
                fase_previa                      //
            );
            if (accion.has_value()) {
                return accion.value();
            }
        }
        // Evalua la preparacion de las pizzas
        int total_preparadas = estado.control_pizzas.obtener_total_preparadas();
        if (total_preparadas < modelo_info::MAXIMO_PIZZAS_PREPARADAS) {
            int maximo =
                modelo_info::MAXIMO_PIZZAS_PREPARADAS - total_preparadas;
            const TiempoJuego tiempo_actual =
                GestorTiempoJuego::obtener_tiempo_juego();
            evaluar_preparacion(
                estado.encargos, contadores, maximo, tiempo_actual
            );
        }

        // En funcion de la fase actual (no necesariamente recien iniciada)
        switch (estado.fase_actual) {
            case FaseNivel::EsperaAntesDeResultado:
                if (timer_espera_antes_de_resultado.termino()) {
                    mostrar_resultado(
                        globales, estado, enlace_vista, timer_fin_nivel, sound
                    );
                }
                break;
            case FaseNivel::MostrandoResultado:
                if (!es_el_ultimo && timer_fin_nivel.termino()) {
                    return AccionGeneral::SiguienteNivel;
                };
                break;
        }

        enlace_vista.actualizarIU(globales.window, estado);
        globales.window.display();
    }
    assert(false); // No deberiamos llegar aqui
    return AccionGeneral::Salir;
}
