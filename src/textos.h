#pragma once

#include "shared.h"
#include <string>

std::string construir_instrucciones(
    const std::string plantilla, const NumNivel &num_nivel, int objetivo
);
std::string construir_resultado();

#define INSTRUCCIONES_NIVEL_ESTATICO                                           \
    "Nivel {num_nivel}.\nDeber%as servir {objetivo} pizzas, de acuerdo con "   \
    "los tipos indicados.\n"                                                   \
    "Recuerda que solo puedes despachar pizzas que ya tengas "                 \
    "preparadas.\n%!Suerte!"

#define INSTRUCCIONES_NIVEL_DINAMICO                                           \
    "Nivel {num_nivel}.\nEn esta ocasi%on deber%as atender los pedidos de "    \
    "pizzas que vayan apareciendo.\n"                                          \
    "%?Podr%as hacerlo?"
