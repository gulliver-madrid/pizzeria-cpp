#pragma once

#include "aplicador.h"
#include "estado_nivel.h"

struct Comando;

struct ModeloAmplio {
    Estado estado;

    ModeloAmplio(const DatosNivel &datos_nivel);
    FaseNivel get_fase_actual();
    std::optional<FaseNivel> aplica_comando( //
        const Comando &comando               //
    );
};
