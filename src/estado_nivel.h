#pragma once

#include "general.h"
#include "modelo/encargos.h"

/* Estado mutable de un nivel */
struct Estado {
    FaseNivel fase_actual = FaseNivel::MostrandoInstrucciones;
    ControlPizzas &control_pizzas;
    Encargos encargos;
    bool establecido = false;
    bool mostrando_grid = false;

    Estado(FaseNivel fase, ControlPizzas &control)
        : fase_actual(fase), control_pizzas(control) {
        assert(encargos.total() == 0);
        establecido = true;
    }
};
