#pragma once

#include "modelo/encargos.h"
#include <cassert>

enum class FaseNivel;
namespace modelo {
    struct ControlPizzas;
}

struct EstadoModelo {
    modelo::ControlPizzas &control_pizzas;
    Encargos encargos;
    GestorTiempoJuego gestor_tiempo;

    EstadoModelo(modelo::ControlPizzas &control);
    void anadir_encargo(dominio::TipoPizza tp);
};

/* Estado mutable de un nivel */
struct Estado {
    FaseNivel fase_actual;
    EstadoModelo estado_modelo;

    bool establecido = false;
    bool mostrando_grid = false;

    Estado(FaseNivel fase, modelo::ControlPizzas &control);
};
