#include "vista.h"
#include "../general.h"
#include "../modelo_amplio/modelo_amplio.h"
#include "../templates/helpers.h"
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
     * Activa o desactiva cada boton despachar segun proceda.
     */
    void activar_botones_despachar_si_procede(
        TipoPizzaToBoton &botones_despachar,
        const ActivacionBotones &activacion_botones
    ) {
        for (auto &[tp, debe_estar_activo] : activacion_botones.despachar) {
            assert(has_key(botones_despachar, tp));
            auto &boton_despachar = botones_despachar.at(tp);
            boton_despachar.activacion_condicional(debe_estar_activo);
        }
    }

    /* Actualiza y dibuja las etiquetas */
    void actualizar_etiquetas(
        sf::RenderTarget &(target),        //
        EtiquetasGenerales &etiquetas,     //
        const ModeloAmplio &modelo_amplio, //
        const sf::Time &tiempo_real_actual //
    ) {
        const modelo::PizzasAContadores &contadores =
            modelo_amplio.modelo_interno.control_pizzas.contadores;

        auto pedidos = modelo_amplio.modelo_interno.control_pizzas.pedidos;
        switch (modelo_amplio.fase_actual) {
            case FaseNivel::MostrandoInstrucciones:
                etiquetas.dibujar_instrucciones(target);
                break;
            case FaseNivel::Activa:
            case FaseNivel::EsperaAntesDeResultado:
                {
                    const auto vista_preparadas =
                        impl::contadores_to_preparadas(contadores);
                    etiquetas.actualizar_contadores(vista_preparadas, pedidos);
                    etiquetas.dibujar_contadores(target);
                    break;
                }

            case FaseNivel::MostrandoResultado:
                etiquetas.dibujar_resultado(target);
                break;
            default:
                break;
        }

        const auto tiempo_juego_actual =
            modelo_amplio.modelo_interno.obtener_tiempo_juego();
        etiquetas.actualizar_barra_estado(
            tiempo_real_actual, tiempo_juego_actual
        );
        etiquetas.dibujar_barra_estado(target);
    }

} // namespace

namespace impl {
    VistaPizzasToStrings contadores_to_preparadas(  //
        const modelo::PizzasAContadores &contadores //
    ) {
        VistaPizzasToStrings textos_preparadas;
        for (auto &[tp, contadores_tp] : contadores) {
            assert(has_key(tipo_pizza_to_string, tp));
            auto &nombre_pizza = tipo_pizza_to_string.at(tp);
            std::string linea =
                nombre_pizza + ": " + std::to_string(contadores_tp.preparadas);
            textos_preparadas[tp] = linea;
        }
        return textos_preparadas;
    }
} // namespace impl

///// Vista (private) /////

// TODO: diferenciar entre actualizacion de datos y dibujado
void Vista::_actualizar_paneles(const EstadoPreparacionPizzas &preparacion //
) {
    // TODO: usar el sistema nativo de dibujo de SFML.
    paneles_completos.actualizar(preparacion);
}
void Vista::_dibujar_paneles(sf::RenderTarget &(target)) const {
    // TODO: usar el sistema nativo de dibujo de SFML.
    target.draw(paneles_completos);
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
    sf::RenderTarget &(target),        //
    const ModeloAmplio &modelo_amplio, //
    const sf::Time &tiempo_real_actual //
) {

    // Limpia la target y empieza a pintar los componentes visuales
    target.clear(colores::COLOR_FONDO);
    if (modelo_amplio.mostrando_grid)
        grid.draw(target, GRID_SIZE, GRID_TONE);

    if ( //
        modelo_amplio.fase_actual == FaseNivel::Activa ||
        modelo_amplio.fase_actual == FaseNivel::EsperaAntesDeResultado
    ) {
        const auto preparacion =
            modelo_amplio.modelo_interno.obtener_estado_preparacion_pizzas();
        _actualizar_paneles(preparacion);
        _dibujar_paneles(target);
    }

    actualizar_etiquetas(target, etiquetas, modelo_amplio, tiempo_real_actual);
    target.draw(botones);
}

void Vista::mostrar_elementos_fase_activa() {
    botones.empezar.visible = false;
    botones.mostrar_botones_nivel(true);
    paneles_completos.visible = true;
}

void Vista::esconder_botones_gestion_pizzeria() { //
    botones.mostrar_botones_nivel(false);
}

void Vista::activar_botones_condicionalmente(
    const ActivacionBotones &activacion_botones
) {
    activar_botones_despachar_si_procede(botones.despachar, activacion_botones);
    for (auto &[_, boton] : botones.encargar) {
        boton.activacion_condicional(activacion_botones.encargar);
    }
}
