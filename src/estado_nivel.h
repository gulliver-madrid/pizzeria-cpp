#pragma once

#include "modelo/encargos.h"
#include <cassert>

enum class FaseNivel;
namespace modelo {
    struct ControlPizzas;
}

/* Estado mutable de un nivel */
struct Estado {
    FaseNivel fase_actual;
    modelo::ControlPizzas &control_pizzas;
    Encargos encargos;
    bool establecido = false;
    bool mostrando_grid = false;

    Estado(FaseNivel fase, modelo::ControlPizzas &control);
};
