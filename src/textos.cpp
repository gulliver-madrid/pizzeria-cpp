#include "textos.h"
#include "vista/cadenas.h"

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_instrucciones(
    const std::string plantilla, //
    const NumNivel &num_nivel,   //
    std::optional<int> objetivo  //
) {
    CadenaJuego cadena = interpolar_unicode(plantilla);
    return cadena
        .interpolar_por_clave(
            "objetivo",                           //
            std::to_string(objetivo.value_or(0)), //
            objetivo.has_value()                  //
        )
        .interpolar_por_clave("num_nivel", std::to_string(num_nivel.valor));
}
std::string construir_resultado() { //
    return interpolar_unicode(RESULTADO_NIVEL_1);
}
