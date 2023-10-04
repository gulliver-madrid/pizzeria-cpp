#include "textos.h"
#include "vista/cadenas.h"

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_instrucciones(
    const std::string plantilla, int num_nivel, int objetivo
) {
    CadenaJuego mi_string = interpolar_unicode(plantilla);
    return mi_string.interpolar_por_clave("objetivo", std::to_string(objetivo))
        .interpolar_por_clave("num_nivel", std::to_string(num_nivel));
}
std::string construir_resultado() { //
    return interpolar_unicode(RESULTADO_NIVEL_1);
}
