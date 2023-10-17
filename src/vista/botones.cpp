#include "botones.h"
#include "../modelo/dominio.h"
#include "basicos_vista.h"
#include "componentes/fabrica_botones.h"
#include "componentes/varios.h"
#include <cassert>

namespace colores {
    namespace botones_encargar {
        const auto FONDO = sf::Color::Green;
        const auto TEXTO = sf::Color::Black;
    } // namespace botones_encargar
    namespace botones_despachar {
        const auto FONDO = sf::Color::Green;
        const auto TEXTO = sf::Color::Black;
    } // namespace botones_despachar
} // namespace colores

///////////////////////////////////////////
// BotonesGenerales
//////////////////////////////////////////

const std::vector<BotonConTexto *> BotonesGenerales::obtener_todos() {
    return {&alternar_grid, &reiniciar, &salir};
}

///////////////////////////////////////////
// Botones
//////////////////////////////////////////

namespace {

    const std::vector<BotonData> datos_botones_generales = {
        {"Salir", sf::Color::Red},             //
        {"Reiniciar", sf::Color(255, 120, 0)}, //
        {"Alternar Grid", sf::Color::Blue}     //
    };

    const BotonData boton_data_botones_despachar{
        "Despachar", colores::botones_despachar::FONDO,
        colores::botones_despachar::TEXTO
    };

    /**
     * Crea y posiciona los botones asociados con la acción "encargar".
     *
     * @param encargar: Mapa donde almacenar los botones creados.
     * @param font: Fuente a utilizar para el texto del botón.
     * @param tp_disponibles: Tipos de pizza disponibles para encargar.
     */
    void _crear_botones_encargar(
        TipoPizzaToBoton &encargar,                //
        const sf::Font &font,                      //
        const modelo::TiposDePizza &tp_disponibles //
    ) {
        // Constantes para definir la posicion de cada boton
        const sf::Vector2f pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_ENCARGAR
        );
        const float pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
        const float pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
        const int diferencia_vertical = 80;

        // Lambda para obtener la posicion de cada boton
        const auto obtener_posicion = [&pos_x, &pos_y_inicial,
                                       &diferencia_vertical //
        ](int indice_boton) {
            const float pos_y =
                pos_y_inicial + (diferencia_vertical * indice_boton);
            return sf::Vector2f(pos_x, pos_y);
        };

        // Lambda para crear boton data
        const auto crear_boton_data = [](modelo::TipoPizza tp) {
            const std::string pizza_str = tipo_pizza_to_string.at(tp);
            return BotonData{
                pizza_str,                        //
                colores::botones_encargar::FONDO, //
                colores::botones_encargar::TEXTO  //
            };
        };

        // Crea los botones
        int i = 0;
        for (auto tp : tp_disponibles) {
            const BotonData boton_data = crear_boton_data(tp);
            const auto posicion = obtener_posicion(i);
            encargar[tp] = crearBotonConTexto(boton_data, posicion, font);
        }
    }

    void _crear_botones_despachar(
        TipoPizzaToBoton &despachar,               //
        const sf::Font &font,                      //
        const modelo::TiposDePizza &tp_disponibles //
    ) {
        const int separacion_vertical_botones = 50;
        const double escala_botones = 0.7;

        // Determinacion posicion inicial
        const auto pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_PREPARADAS
        );
        const auto pos_x_relativa_panel =
            medidas::MARGEN_IZQ_ETIQUETAS + (medidas::ANCHO_PANEL * 0.55);
        const float pos_x = pos_panel.x + pos_x_relativa_panel;
        const float pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;

        // Lambda para obtener la posicion de cada boton
        const auto obtener_posicion = [&pos_x, &pos_y_inicial,
                                       &separacion_vertical_botones //
        ](size_t indice_boton) {
            const float pos_y =
                pos_y_inicial + (separacion_vertical_botones * indice_boton);
            return sf::Vector2f(pos_x, pos_y);
        };

        size_t i = 0;
        for (auto tp : tp_disponibles) {
            const auto posicion = obtener_posicion(i++);
            despachar[tp] = crearBotonConTexto(
                boton_data_botones_despachar, posicion, font, Align::Left,
                escala_botones
            );
        }
    }

    void _crear_botones_generales(
        BotonesGenerales &generales, //
        const sf::Font &font         //
    ) {
        const sf::Vector2f pos_ultimo_panel =
            basicos_vista::obtener_posicion_panel( //
                IndicePanel::PANEL_PEDIDOS
            );
        const float pos_dcha_ultimo_boton =
            pos_ultimo_panel.x + medidas::ANCHO_PANEL;

        auto botones_generales = crear_botones_alineados_derecha(
            {pos_dcha_ultimo_boton, medidas::FILA_BOTONES_GENERALES}, //
            datos_botones_generales,                                  //
            font,                                                     //
            medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES    //
        );

        assert(botones_generales.size() == 3);
        generales.salir = botones_generales[0];
        generales.reiniciar = botones_generales[1];
        generales.alternar_grid = botones_generales[2];
    }
} // namespace

/* Crea todos los botones */
Botones::Botones(
    const sf::Font &font, const modelo::TiposDePizza &tp_disponibles
) {
    auto empezar_data =
        BotonData{std::string("Empezar"), sf::Color::Green, sf::Color::Black};
    empezar = crearBotonConTexto(empezar_data, sf::Vector2f(500, 450), font);

    _crear_botones_encargar(encargar, font, tp_disponibles);
    _crear_botones_despachar(despachar, font, tp_disponibles);
    _crear_botones_generales(generales, font);

    todos = {&empezar};
    const int num_fijos = todos.size();
    for (auto &boton : generales.obtener_todos()) {
        todos.push_back(boton);
    }
    for (auto &[_, boton] : despachar) {
        todos.push_back(&boton);
    }
    for (auto &[_, boton] : encargar) {
        todos.push_back(&boton);
    }
}

void Botones::dibujar(sf::RenderWindow &ventana) const {
    for (auto boton_ptr : todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->dibujar(ventana);
    }
}

void Botones::mostrar_botones_nivel(bool nuevo_valor) {
    for (auto &[_, boton] : despachar) {
        boton.visible = nuevo_valor;
    }
    for (auto &[_, boton] : encargar) {
        boton.visible = nuevo_valor;
    }
}
