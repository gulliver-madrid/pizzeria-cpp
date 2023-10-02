#pragma once

#include "general.h"
#include "vista/grid.h"

struct Globales;

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

AccionGeneral nivel(               //
    Globales &globales,            //
    const DatosNivel &datos_nivel, //
    int num_nivel,                 //
    Grid &grid,                    //
    bool es_el_ultimo
);
