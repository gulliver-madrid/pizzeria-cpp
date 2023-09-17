#pragma once

#include <string>

std::string construir_instrucciones(std::string plantilla, int objetivo);
std::string construir_resultado();

#define INSTRUCCIONES_NIVEL_1                                                  \
    "Nivel 1.\nEl objetivo del juego es gestionar con exito tu "               \
    "pizzer%ia.\nTu primera misi%on es servir a {num_clientes} clientes.\n"    \
    "Recuerda que solo puedes despachar pizzas que ya tengas "                 \
    "preparadas.\n%!Suerte!"

#define INSTRUCCIONES_NIVEL_2                                                  \
    "Nivel 2.\nEn esta ocasi%on los clientes llegan cuando todav%ia no hay "   \
    "suficientes pizzas preparadas.\n"                                         \
    "%?Podr%as resolver el reto?"
