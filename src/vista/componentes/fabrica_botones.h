#pragma once

#include "boton_con_texto.h"

std::vector<BotonConTexto> crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,        //
    const std::vector<BotonData> &datos_botones, //
    const sf::Font &font,                        //
    int separacion                               //
);

void colocar_botones_en_vertical(
    const std::vector<BotonConTexto *> &botones, //
    const sf::Vector2f &pos_inicial,             //
    float diferencia                             //
);
