#include "textos.h"
#include "log_init.h"
#include "vista/cadenas.h"
#include <iostream>

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_texto_instrucciones(
    const std::string &plantilla,     //
    const NumNivelOpcional &num_nivel //
) {
    CadenaJuego cadena = interpolar_unicode(plantilla);
    return cadena.interpolar_por_clave("num_nivel", num_nivel.to_string());
}

std::string construir_resultado() { //
    return interpolar_unicode(RESULTADO_NIVEL_1);
}
