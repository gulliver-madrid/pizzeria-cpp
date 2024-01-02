#pragma once

#include "estado_nivel.h"
#include "general.h"

struct DatosNivel;

struct ModeloAmplio {
    Estado estado;
    FaseNivel get_fase_actual() { return estado.fase_actual; }
    ModeloAmplio(const DatosNivel &datos_nivel)
        : estado(FaseNivel::MostrandoInstrucciones, datos_nivel) {}
};
