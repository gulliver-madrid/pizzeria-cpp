#pragma once

#include "cadenas.h"
#include <string>
#include <vector>

struct VistaPreparacionPizza {
    std::string nombre_pizza;
    int porcentaje;
};

using PresentacionPreparacionPizzas = std::vector<VistaPreparacionPizza>;

struct VistaBarraEstado {
    CadenaJuego texto;
};
