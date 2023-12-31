#pragma once

#include "control_pizzas.h"
#include "encargos.h"

struct DatosNivelParaModelo {
    modelo::Pedidos pedidos;
    const EsSistemaEstatico es_estatico;
    DatosNivelParaModelo(modelo::Pedidos pedidos, bool es_estatico = false)
        : pedidos(pedidos), es_estatico(EsSistemaEstatico(es_estatico)) {}
};
