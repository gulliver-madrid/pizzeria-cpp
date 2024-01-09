#pragma once

#include "modelo/datos_modelo_interno.h"
#include <string>

/* Guarda la informacion relativa al nivel */
struct DatosNivel {
    std::string instrucciones;
    DatosModeloInterno datos_modelo_interno;
    DatosNivel(std::string instrucciones = "", modelo::Pedidos pedidos = {})
        : instrucciones(instrucciones), datos_modelo_interno(pedidos) {}
};
