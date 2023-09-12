#include "textos.h"
#include "cadenas.h"

#include <string>

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_instrucciones(std::string plantilla) {
    return interpolar(plantilla);
}
std::string construir_resultado() { //
    return interpolar(RESULTADO_NIVEL_1);
}
