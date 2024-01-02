#pragma once

#include "modelo/datos_nivel_para_modelo.h"
#include <string>

/* Guarda la informacion relativa al nivel */
struct DatosNivel {
    std::string instrucciones;
    DatosNivelParaModelo datos_nivel_para_modelo;
    DatosNivel(
        std::string instrucciones = "", modelo::Pedidos pedidos = {},
        bool es_estatico = false
    )
        : instrucciones(instrucciones),
          datos_nivel_para_modelo(pedidos, es_estatico) {}

    EsSistemaEstatico es_estatico() const {
        return datos_nivel_para_modelo.es_estatico;
    }
};
