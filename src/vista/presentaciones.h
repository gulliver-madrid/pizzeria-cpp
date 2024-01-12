#pragma once

#include <string>
#include <vector>

struct VistaPreparacionPizza {
    std::string nombre_pizza;
    int porcentaje;
};

using VistaPreparacionPizzas = std::vector<VistaPreparacionPizza>;
