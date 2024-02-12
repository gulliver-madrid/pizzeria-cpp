#pragma once

#include "../vista_shared.h"
#include "boton_con_texto.h"

void alinear_botones_derecha(
    const Botones &botones,                   //
    const PosicionRelativa &posicion_inicial, //
    float separacion                          //
);

void colocar_botones_en_vertical(
    const std::vector<std::shared_ptr<BotonConTexto>> &botones, //
    const PosicionRelativa &pos_inicial,                        //
    float diferencia,                                           //
    const sf::FloatRect &contenedor                             //
);
