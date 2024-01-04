#include "vista.h"
#include "../estado_nivel.h"
#include "../general.h"
#include "basicos_vista.h"
#include "grid.h"
#include "vista_data.h"
#include <SFML/System/Time.hpp>
#include <cassert>
#include <iostream>
#include <map>
#include <string>

using dominio::TipoPizza;
using dominio::TiposDePizza;

namespace {
    /*
     * Activa o desactiva cada boton despachar dependiendo de si hay pizzas
     * preparadas de ese tipo.
     */
    void activar_botones_despachar_si_hay_preparadas(
        TipoPizzaToBoton &botones_despachar,
        const modelo::PizzasAContadores &contadores
    ) {
        for (auto &[tp, contadores_tp] : contadores) {
            auto &boton_despachar = botones_despachar.at(tp);
            boton_despachar.activacion_condicional(
                contadores_tp.preparadas > 0
            );
        }
    }

    /* Actualiza el estado de los botones en funcion de varios factores */
    void actualizar_estado_botones(BotonesApp &botones, const Estado &estado) {
        const auto &control_pizzas = estado.estado_modelo.control_pizzas;
        // Botones despachar
        const modelo::PizzasAContadores &contadores = control_pizzas.contadores;
        activar_botones_despachar_si_hay_preparadas(
            botones.despachar, contadores
        );

        // Botones encargar
        constexpr int maximo = modelo_info::MAXIMO_PIZZAS_EN_PREPARACION;
        const int en_preparacion = estado.estado_modelo.encargos.total();
        assert(en_preparacion <= maximo);
        const bool se_pueden_preparar_mas = en_preparacion < maximo;

        for (auto &[_, boton] : botones.encargar) {
            boton.activacion_condicional(se_pueden_preparar_mas);
        }
    }

    /* Actualiza y dibuja las etiquetas */
    void actualizar_etiquetas(
        sf::RenderWindow &ventana,         //
        EtiquetasGenerales &etiquetas,     //
        const Estado &estado,              //
        const sf::Time &tiempo_real_actual //
    ) {
        const modelo::PizzasAContadores &contadores =
            estado.estado_modelo.control_pizzas.contadores;

        auto pedidos = estado.estado_modelo.control_pizzas.pedidos;
        switch (estado.fase_actual) {
            case FaseNivel::MostrandoInstrucciones:
                etiquetas.dibujar_instrucciones(ventana);
                break;
            case FaseNivel::Activa:
            case FaseNivel::EsperaAntesDeResultado:
                etiquetas.actualizar_y_dibujar_contadores(
                    contadores, pedidos, ventana
                );
                break;
            case FaseNivel::MostrandoResultado:
                etiquetas.dibujar_resultado(ventana);
                break;
            default:
                break;
        }

        const auto tiempo_juego_actual =
            estado.estado_modelo.obtener_tiempo_juego();
        etiquetas.actualizar_barra_estado(
            tiempo_real_actual, tiempo_juego_actual
        );
        etiquetas.dibujar_barra_estado(ventana);
    }

} // namespace

namespace impl {
    std::map<TipoPizza, std::string> contadores_to_preparadas( //
        modelo::PizzasAContadores &contadores                  //
    ) {
        std::map<dominio::TipoPizza, std::string> textos_preparadas;
        for (auto &[tp, contadores_tp] : contadores) {
            auto &nombre_pizza = tipo_pizza_to_string.at(tp);
            std::string linea =
                nombre_pizza + ": " + std::to_string(contadores_tp.preparadas);
            textos_preparadas[tp] = linea;
        }
        return textos_preparadas;
    }
} // namespace impl
// namespace impl

///// Vista (private) /////

void Vista::_actualizar_paneles(
    sf::RenderWindow &ventana,                 //
    PanelesCompletos &paneles_completos,       //
    const EstadoPreparacionPizzas &preparacion //
) {
    paneles_completos.dibujar(ventana, preparacion);
}

///// Vista (public) /////

Vista::Vista(
    const sf::Font &font,                       //
    Grid &grid,                                 //
    const dominio::TiposDePizza &tp_disponibles //
)
    : ObjetoConFont(font),           //
      botones(font, tp_disponibles), //
      paneles_completos(font),       //
      etiquetas(font),               //
      grid(grid),                    //
      tp_disponibles(tp_disponibles) {}

void Vista::setup(
    const std::string &instrucciones, //
    const NumNivel &num_nivel         //
) {
    etiquetas.setup(
        instrucciones, //
        num_nivel,     //
        tp_disponibles //
    );
    // Mostrar botones iniciales
    botones.generales.alternar_grid.visible = MODO_DESARROLLO;
    botones.generales.reiniciar.visible = true;
    botones.generales.salir.visible = true;
    botones.empezar.visible = true;
}

/*
 * Actualiza el interfaz grafico
 */
void Vista::actualizarIU(              //
    sf::RenderWindow &ventana,         //
    const Estado &estado,              //
    const sf::Time &tiempo_real_actual //
) {
    actualizar_estado_botones(botones, estado);

    // Limpia la ventana y empieza a pintar los componentes visuales
    ventana.clear(colores::COLOR_FONDO);
    if (estado.mostrando_grid)
        grid.draw(ventana, GRID_SIZE, GRID_TONE);

    if ( //
        estado.fase_actual == FaseNivel::Activa ||
        estado.fase_actual == FaseNivel::EsperaAntesDeResultado
    ) {
        const auto preparacion =
            estado.estado_modelo.obtener_estado_preparacion_pizzas();
        _actualizar_paneles(ventana, paneles_completos, preparacion);
    }

    actualizar_etiquetas(ventana, etiquetas, estado, tiempo_real_actual);
    botones.dibujar(ventana);
}

void Vista::mostrar_elementos_fase_activa() {
    botones.empezar.visible = false;
    botones.mostrar_botones_nivel(true);
    paneles_completos.visible = true;
}

void Vista::esconder_botones_gestion_pizzeria() { //
    botones.mostrar_botones_nivel(false);
}
