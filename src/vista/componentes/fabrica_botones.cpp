#include "fabrica_botones.h"
#include "varios.h"
#include <cassert>

namespace medidas {
    constexpr int MARGEN_BOTON = 20;
    constexpr int TAMANO_TEXTO_BOTONES = 32;
} // namespace medidas

/* Crea un botón rectangular con texto */
BotonConTexto crearBotonConTexto(
    const BotonData &boton_data,  //
    const sf::Vector2f &posicion, //
    const sf::Font &font,         //
    Align align,                  //
    double escala                 //
) {
    // La escala del margen es proporcional al cuadrado de la escala del botón
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus límites en el Rect
    sf::Text etiqueta = crearEtiqueta(
        medidas::TAMANO_TEXTO_BOTONES * escala, boton_data.color_texto, font
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

/*
 * Crea una hilera de botones alienados a la derecha. El orden en el que se
 * reciben los datos y se anaden al vector de botones es de derecha a izquierda.
 */
std::vector<BotonConTexto> crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,        //
    const std::vector<BotonData> &datos_botones, //
    const sf::Font &font,                        //
    int separacion
) {
    std::vector<BotonConTexto> botones;
    int next_pos_x = posicion_inicial.x;
    for (auto &dato : datos_botones) {
        const auto posicion = sf::Vector2f(next_pos_x, posicion_inicial.y);
        botones.push_back( //
            crearBotonConTexto(dato, posicion, font, Align::Right)
        );
        const auto anterior_izquierda = botones.back().getGlobalBounds().left;
        next_pos_x = anterior_izquierda - separacion;
    }
    return botones;
}
