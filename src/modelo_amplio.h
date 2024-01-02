#pragma once

#include "estado_nivel.h"
#include "general.h"

struct DatosNivel;
struct Comando;

struct ModeloAmplio {
    Estado estado;
    FaseNivel get_fase_actual() { return estado.fase_actual; }
    ModeloAmplio(const DatosNivel &datos_nivel)
        : estado(FaseNivel::MostrandoInstrucciones, datos_nivel) {}

    FaseNivel aplica_comando(  //
        const Comando &comando //
    ) {
        return FaseNivel::Saliendo;
    }
};
