#pragma once

#include "control_pizzas.h"
#include "encargos.h"

struct DatosNivelParaModelo {
    modelo::Pedidos pedidos;
    DatosNivelParaModelo(modelo::Pedidos pedidos) : pedidos(pedidos) {}
};
