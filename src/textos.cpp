#include "textos.h"
#include "cadenas.h"

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_instrucciones(const std::string plantilla, int objetivo) {
    CadenaJuego mi_string = interpolar_unicode(plantilla);
    return mi_string.interpolar_por_clave(
        "num_clientes", std::to_string(objetivo)
    );
}
std::string construir_resultado() { //
    return interpolar_unicode(RESULTADO_NIVEL_1);
}
