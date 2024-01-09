#pragma once

#include "../modelo/datos_modelo_interno.h"
#include "../modelo/modelo_interno.h"

struct Comando;
enum class FaseNivel;

struct ModeloAmplio {
    FaseNivel fase_actual;
    ModeloInterno modelo_interno;

    bool establecido = false;
    bool mostrando_grid = false;

    ModeloAmplio::ModeloAmplio(const DatosModeloInterno &datos_modelo_interno);

    FaseNivel get_fase_actual();
};
