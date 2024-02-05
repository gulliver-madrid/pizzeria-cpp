#pragma once

#include "cadenas.h"
#include <string>
#include <vector>

struct VistaPreparacionPizza {
    std::string nombre_pizza;
    int porcentaje;
};

struct VistaBarraEstado {
    CadenaJuego texto;
};

struct VistaPedido {
    std::vector<std::string> cadenas;
    size_t num_items;
};
