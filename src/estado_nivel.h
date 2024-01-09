#pragma once

#include "modelo/modelo_interno.h"

enum class FaseNivel;
struct DatosNivel;

/* Estado mutable de un nivel */
struct Estado {
    FaseNivel fase_actual;
    ModeloInterno modelo_interno;

    bool establecido = false;
    bool mostrando_grid = false;

    Estado(FaseNivel fase, const DatosNivel &);
};
