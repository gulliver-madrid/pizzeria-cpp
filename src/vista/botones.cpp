#include "botones.h"
#include "../modelo/dominio.h"
#include "basicos_vista.h"
#include "componentes/fabrica_botones.h"
#include "componentes/varios.h"
#include <cassert>

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

    void _crear_botones_encargar(
        TipoPizzaToBoton &encargar,                //
        const sf::Font &font,                      //
        const modelo::TiposDePizza &tp_disponibles //
    ) {
        int i = 0;
        for (auto tp : tp_disponibles) {
            auto pos_panel = basicos_vista::obtener_posicion_panel(
                IndicePanel::PANEL_ENCARGAR
            );
            BotonData encargar_tp_data{
                tipo_pizza_to_string[tp], sf::Color::Green, sf::Color::Black
            };
            encargar[tp] = crearBotonConTexto(
                encargar_tp_data,
                sf::Vector2f(
                    pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS,
                    pos_panel.y + medidas::FILA_CONTENIDO_PANEL + 80 * i
                ),
                font
            );
            i++;
        }
    }
    void _crear_botones_despachar(
        TipoPizzaToBoton &despachar,               //
        const sf::Font &font,                      //
        const modelo::TiposDePizza &tp_disponibles //
    ) {
        const auto pos_x_boton_despachar_rel_panel =
            medidas::MARGEN_IZQ_ETIQUETAS + (medidas::ANCHO_PANEL * 0.55);
        const BotonData despachar_tp{
            "Despachar", sf::Color::Green, sf::Color::Black
        };
        const int separacion_vertical_botones_despachar = 50;
        const double escala_botones_despachar = 0.7;

        size_t i = 0;
        for (auto tp : tp_disponibles) {
            auto pos_panel = basicos_vista::obtener_posicion_panel( //
                IndicePanel::PANEL_PREPARADAS
            );
            const auto pos_x = pos_panel.x + pos_x_boton_despachar_rel_panel;
            const auto pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL +
                               (separacion_vertical_botones_despachar * i);
            despachar[tp] = crearBotonConTexto(
                despachar_tp, sf::Vector2f(pos_x, pos_y), font, Align::Left,
                escala_botones_despachar
            );
            i++;
        }
    }

    void _crear_botones_generales(
        BotonesGenerales &generales, //
        const sf::Font &font         //
    ) {
        const auto pos_ultimo_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_PEDIDOS
        );
        const auto pos_dcha_ultimo_boton =
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
