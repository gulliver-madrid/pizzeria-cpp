#include "textos.h"
#include "vista/cadenas.h"

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_instrucciones(
    const std::string plantilla,              //
    const std::shared_ptr<NumNivel> num_nivel //
) {
    CadenaJuego cadena = interpolar_unicode(plantilla);
    return cadena

        .interpolar_por_clave("num_nivel", std::to_string(num_nivel->valor));
}
std::string construir_resultado() { //
    return interpolar_unicode(RESULTADO_NIVEL_1);
}
