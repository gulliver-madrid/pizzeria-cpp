#pragma once

#include <string>

std::string construir_instrucciones(std::string plantilla);
std::string construir_resultado();

#define INSTRUCCIONES_NIVEL_1                                                  \
    "Pizzer%ia.\nEl objetivo del juego es gestionar con exito tu "             \
    "pizzer%ia.\nTu primera misi%on es servir a 5 clientes "                   \
    "satisfechos.\n%!Suerte!"
#define INSTRUCCIONES_NIVEL_2                                                  \
    "Eso estuvo muy bien, pero el truco es que ten%iamos las pizzas ya "       \
    "preparadas: normalmente\nhabr%a que mandarlas preparar conforme los "     \
    "clientes las demandan.\n"                                                 \
    "Tu siguiente misi%on es atender con %exito a 10 clientes."                \
    "\n%!Suerte!"
