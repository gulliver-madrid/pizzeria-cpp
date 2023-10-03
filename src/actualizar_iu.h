#pragma once

#include "vista/vista.h"

struct Estado;
struct Grid;

struct Vista {
    Botones &botones;
    PanelesCompletos &paneles_completos;
    EtiquetasGenerales &etiquetas;
    Grid &grid;
    void actualizarIU(             //
        sf::RenderWindow &ventana, //
        const Estado &estado,      //
        sf::Font font              //
    );
};
