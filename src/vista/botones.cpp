#include "botones.h"
#include "../modelo/dominio.h"
#include "componentes/varios.h"
#include "vista_basics.h"
#include <cassert>

namespace medidas {
    constexpr int MARGEN_BOTON = 20;
    constexpr int TAMANO_TEXTO_BOTONES = 32;
} // namespace medidas

struct BotonData {
    std::string texto;
    sf::Color color_fondo;
    sf::Color color_texto = sf::Color::White;
};

/* Crea un botón rectangular con texto */
BotonConTexto crearBotonConTexto(
    const BotonData &boton_data,  //
    const sf::Vector2i &posicion, //
    const sf::Font &font,         //
    Align align,                  //
    double escala                 //
) {
    // La escala del margen es proporcional al cuadrado de la escala del botón
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus límites en el Rect
    sf::Text etiqueta = crearEtiqueta(
        medidas::TAMANO_TEXTO_BOTONES * escala, font, boton_data.color_texto
    );
    etiqueta.setString(boton_data.texto);
    sf::FloatRect textRect = etiqueta.getGlobalBounds();

    // Rect
    sf::RectangleShape rect(
        sf::Vector2f(textRect.width + margen * 2, textRect.height + margen * 2)
    );
    rect.setFillColor(boton_data.color_fondo);
    int x;
    if (align == Align::Left) {
        x = posicion.x;
    } else {
        assert(align == Align::Right);
        x = posicion.x - rect.getGlobalBounds().width;
    }
    int y = posicion.y;
    rect.setPosition(x, y);
    // Ajustamos para evitar un margen excesivo arriba y a la izquierda
    etiqueta.setPosition(x + margen * 0.7, y + margen * 0.7);

    return BotonConTexto(rect, etiqueta);
};

/* Crea todos los botones */
Botones::Botones(
    const sf::Font &font, const std::vector<TipoPizza> &tp_disponibles
) {
    auto empezar_data =
        BotonData{std::string("Empezar"), sf::Color::Green, sf::Color::Black};
    empezar = crearBotonConTexto(empezar_data, sf::Vector2i(500, 450), font);
    int i = 0;
    for (auto tp : tp_disponibles) {
        auto pos_panel = obtener_posicion_panel(IndicePanel::PANEL_ENCARGAR);
        BotonData encargar_tp_data{
            tipo_pizza_to_string[tp], sf::Color::Green, sf::Color::Black};
        encargar[tp] = crearBotonConTexto(
            encargar_tp_data,
            sf::Vector2i(
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
            sf::Vector2i(
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
    salir = crearBotonConTexto(
        BotonData{"Salir", sf::Color::Red},
        sf::Vector2i(pos_dcha_ultimo_boton, medidas::FILA_BOTONES_GENERALES),
        font, Align::Right
    );
    int next_pos = salir.getGlobalBounds().left -
                   medidas::SEPARACION_ENTRE_BOTONES_GENERALES;
    reiniciar = crearBotonConTexto(
        BotonData{"Reiniciar", sf::Color(255, 120, 0)},
        sf::Vector2i(next_pos, medidas::FILA_BOTONES_GENERALES), font,
        Align::Right
    );
    next_pos = reiniciar.getGlobalBounds().left -
               medidas::SEPARACION_ENTRE_BOTONES_GENERALES;
    alternar_grid = crearBotonConTexto(
        BotonData{"Alternar Grid", sf::Color::Blue},
        sf::Vector2i(next_pos, medidas::FILA_BOTONES_GENERALES), font,
        Align::Right
    );

    todos = {&empezar, &alternar_grid, &reiniciar, &salir};
    const int num_fijos = todos.size();
    for (auto &par : despachar) {
        todos.push_back(&par.second);
    }
    for (auto &par : encargar) {
        todos.push_back(&par.second);
    }
    assert(todos.size() == (num_fijos + tp_disponibles.size() * 2));
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
