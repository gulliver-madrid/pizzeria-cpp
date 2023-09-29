#pragma once

#include "general.h"
#include "modelo/modelo.h"
#include "vista/grid.h"

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

AccionGeneral nivel(               //
    Globales &globales,            //
    const DatosNivel &datos_nivel, //
    Grid &grid,                    //
    bool es_el_ultimo
);
