#pragma once

#include "shared.h"
#include <memory>
#include <optional>
#include <string>

std::string construir_instrucciones(
    const std::string plantilla,    //
    const std::shared_ptr<NumNivel> //
);
std::string construir_resultado();

#define INSTRUCCIONES_NIVEL_DINAMICO                                           \
    "Nivel {num_nivel}.\nTu tarea es atender los pedidos de "                  \
    "pizzas que vayan apareciendo.\n"                                          \
    "%!Suerte!"
