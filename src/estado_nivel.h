#pragma once

#include "modelo/estado_modelo.h"

enum class FaseNivel;
struct DatosNivel;

/* Estado mutable de un nivel */
struct Estado {
    FaseNivel fase_actual;
    EstadoModelo estado_modelo;

    bool establecido = false;
    bool mostrando_grid = false;

    Estado(FaseNivel fase, const DatosNivel &);
};
