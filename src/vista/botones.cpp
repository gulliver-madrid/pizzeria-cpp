#include "botones.h"
#include "../modelo/dominio.h"
#include "componentes/fabrica_botones.h"
#include "componentes/varios.h"
#include "vista_basics.h"
#include <cassert>

const std::vector<BotonConTexto *> BotonesGenerales::obtener_todos() {
    return {&alternar_grid, &reiniciar, &salir};
}

/* Crea todos los botones */
Botones::Botones(
    const sf::Font &font, const std::vector<modelo::TipoPizza> &tp_disponibles
) {
    auto empezar_data =
        BotonData{std::string("Empezar"), sf::Color::Green, sf::Color::Black};
    empezar = crearBotonConTexto(empezar_data, sf::Vector2f(500, 450), font);
    int i = 0;
    for (auto tp : tp_disponibles) {
        auto pos_panel = obtener_posicion_panel(IndicePanel::PANEL_ENCARGAR);
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
    i = 0;
    for (auto tp : tp_disponibles) {
        auto pos_panel = obtener_posicion_panel(IndicePanel::PANEL_PREPARADAS);
        BotonData despachar_tp{"Despachar", sf::Color::Green, sf::Color::Black};
        despachar[tp] = crearBotonConTexto(
            despachar_tp,
            sf::Vector2f(
                pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS +
                    (medidas::ANCHO_PANEL * 0.55),
                pos_panel.y + medidas::FILA_CONTENIDO_PANEL + 50 * i
            ),
            font, Align::Left, 0.7
        );
        i++;
    }
    // Botones generales
    const auto pos_ultimo_panel =
        obtener_posicion_panel(IndicePanel::PANEL_PEDIDOS);
    const auto pos_dcha_ultimo_boton =
        pos_ultimo_panel.x + medidas::ANCHO_PANEL;

    const std::vector<BotonData> datos_botones = {
        {"Salir", sf::Color::Red},             //
        {"Reiniciar", sf::Color(255, 120, 0)}, //
        {"Alternar Grid", sf::Color::Blue}     //
    };

    auto botones_generales = crear_botones_alineados_derecha(
        {pos_dcha_ultimo_boton, medidas::FILA_BOTONES_GENERALES}, //
        datos_botones,                                            //
        font,                                                     //
        medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES    //
    );

    assert(botones_generales.size() == 3);
    generales.salir = botones_generales[0];
    generales.reiniciar = botones_generales[1];
    generales.alternar_grid = botones_generales[2];

    todos = {&empezar};
    const int num_fijos = todos.size();
    for (auto &boton : generales.obtener_todos()) {
        todos.push_back(boton);
    }
    for (auto &par : despachar) {
        todos.push_back(&par.second);
    }
    for (auto &par : encargar) {
        todos.push_back(&par.second);
    }
}

void Botones::dibujar(sf::RenderWindow &ventana) const {
    for (auto boton_ptr : todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->dibujar(ventana);
    }
}

void Botones::mostrar_botones_nivel(bool nuevo_valor) {
    for (auto &par : despachar) {
        auto &boton = par.second;
        boton.visible = nuevo_valor;
    }
    for (auto &par : encargar) {
        auto &boton = par.second;
        boton.visible = nuevo_valor;
    }
}
