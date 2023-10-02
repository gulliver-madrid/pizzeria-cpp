#include "botones.h"
#include "../modelo/dominio.h"
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
    float escala
) {
    int x = posicion.x;
    int y = posicion.y;
    // La escala del margen es proporcional al cuadrado de la escala del botón
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus límites en el Rect
    sf::Text etiqueta = crearEtiqueta(
        medidas::TAMANO_TEXTO_BOTONES * escala, font, boton_data.color_texto
    );
    etiqueta.setString(boton_data.texto);
    // Ajustamos para evitar un margen excesivo arriba y a la izquierda
    etiqueta.setPosition(x + margen * 0.7, y + margen * 0.7);
    sf::FloatRect textRect = etiqueta.getGlobalBounds();

    // Rect
    sf::RectangleShape rect(
        sf::Vector2f(textRect.width + margen * 2, textRect.height + margen * 2)
    );
    rect.setFillColor(boton_data.color_fondo);
    rect.setPosition(x, y);

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
            font, 0.7
        );
        i++;
    }

    reiniciar = crearBotonConTexto(
        BotonData{"Reiniciar", sf::Color::Blue},
        sf::Vector2i(1440, medidas::FILA_BOTONES_GENERALES), font
    );
    salir = crearBotonConTexto(
        BotonData{"Salir", sf::Color::Red},
        sf::Vector2i(1640, medidas::FILA_BOTONES_GENERALES), font
    );

    todos = {&empezar, &reiniciar, &salir};
    for (auto &par : despachar) {
        todos.push_back(&par.second);
    }
    for (auto &par : encargar) {
        todos.push_back(&par.second);
    }
    assert(todos.size() == 3 + tp_disponibles.size() * 2);
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
