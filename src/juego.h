#pragma once

#include "dominio.h"
#include "tiempo.h"

int juego();

struct EncargoACocina {
    TipoPizza tipo;
    TiempoPreparacion tiempo_preparacion;
};

int encargadas_del_tipo(
    std::vector<EncargoACocina> &encargadas, TipoPizza tipo
);
