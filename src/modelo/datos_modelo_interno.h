#pragma once

#include "control_pizzas.h"

struct DatosModeloInterno {
    modelo::Pedidos pedidos;
    DatosModeloInterno(modelo::Pedidos pedidos) : pedidos(pedidos) {}
};
