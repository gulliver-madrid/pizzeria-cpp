#pragma once

#include "boton_con_texto.h"
#include "boton_data.h"

BotonConTexto crearBotonConTexto(
    const BotonData &boton_data,  //
    const sf::Vector2f &posicion, //
    const sf::Font &font,         //
    Align align = Align::Left,    //
    double escala = 1             //
);

std::vector<BotonConTexto> crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,        //
    const std::vector<BotonData> &datos_botones, //
    const sf::Font &font,                        //
    int separacion
);
