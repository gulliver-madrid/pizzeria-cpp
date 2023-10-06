#pragma once

#include "general.h"
#include "shared.h"
#include "vista/grid.h"

struct Globales;

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

AccionGeneral nivel(               //
    Globales &globales,            //
    const DatosNivel &datos_nivel, //
    NumNivel num_nivel,            //
    Grid &grid,                    //
    bool es_el_ultimo
);
