#include "textos.h"
#include "cadenas.h"

#include <string>

#define INSTRUCCIONES_NIVEL_1                                                  \
    "Pizzer%ia.\nEl objetivo del juego es gestionar con exito tu "             \
    "pizzer%ia.\nTu primera misi%on es conseguir 5 clientes "                  \
    "satisfechos.\n%!Suerte!"
#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_instrucciones() {
    return interpolar(INSTRUCCIONES_NIVEL_1);
}
std::string construir_resultado() { //
    return interpolar(RESULTADO_NIVEL_1);
}
