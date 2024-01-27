#pragma once

#include "../vista_shared.h"
#include "boton_con_texto.h"

void alinear_botones_derecha(
    const Botones &botones,               //
    const sf::Vector2f &posicion_inicial, //
    float separacion                      //
);

Botones crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,              //
    const std::vector<BotonData> &datos_botones,       //
    const sf::FloatRect &contenedor = sf::FloatRect(), //
    float separacion = 0                               //
);

void colocar_botones_en_vertical(
    const std::vector<std::shared_ptr<BotonConTexto>> &botones, //
    const sf::Vector2f &pos_inicial,                            //
    float diferencia                                            //
);
