#include "textos.h"
#include "cadenas.h"

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_instrucciones(std::string plantilla, int objetivo) {
    return replace_placeholder(
        interpolar(plantilla), "num_clientes", std::to_string(objetivo)
    );
}
std::string construir_resultado() { //
    return interpolar(RESULTADO_NIVEL_1);
}
