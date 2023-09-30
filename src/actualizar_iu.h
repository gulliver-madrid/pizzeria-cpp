#pragma once

#include "vista/vista.h"

struct Estado;
struct Grid;

void actualizarIU(                       //
    sf::RenderWindow &ventana,           //
    Botones &botones,                    //
    PanelesCompletos &paneles_completos, //
    EtiquetasGenerales &etiquetas,       //
    Estado &estado,                      //
    Grid &grid,                          //
    sf::Font font                        //
);
