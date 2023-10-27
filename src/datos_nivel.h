#pragma once

#include "modelo/control_pizzas.h"
#include <string>

/* Guarda la información relativa al nivel */
struct DatosNivel {
    std::string instrucciones;
    modelo::Pedidos pedidos;
    const EsSistemaEstatico es_estatico;
    DatosNivel(
        std::string instrucciones, modelo::Pedidos pedidos,
        bool es_estatico = false
    )
        : instrucciones(instrucciones), pedidos(pedidos),
          es_estatico(EsSistemaEstatico(es_estatico)) {}
};
