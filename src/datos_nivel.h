#pragma once

#include "modelo/datos_nivel_para_modelo.h"
#include <string>

/* Guarda la informacion relativa al nivel */
struct DatosNivel {
    std::string instrucciones;
    DatosNivelParaModelo datos_nivel_para_modelo;
    DatosNivel(std::string instrucciones = "", modelo::Pedidos pedidos = {})
        : instrucciones(instrucciones), datos_nivel_para_modelo(pedidos) {}
};
