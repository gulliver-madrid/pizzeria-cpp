#pragma once

#include "boton_con_texto.h"

std::vector<BotonConTexto> crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,               //
    const std::vector<BotonDataConFont> &datos_botones, //
    const sf::FloatRect &contenedor = sf::FloatRect(),  //
    int separacion = 0                                  //
);

void colocar_botones_en_vertical(
    const std::vector<BotonConTexto *> &botones, //
    const sf::Vector2f &pos_inicial,             //
    float diferencia                             //
);
