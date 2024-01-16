#include "textos.h"
#include "log_init.h"
#include "vista/cadenas.h"
#include <iostream>

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_texto_instrucciones(
    const std::string &plantilla,           //
    const std::optional<NumNivel> num_nivel //
) {
    std::cout << "En construir_texto_instrucciones()" << std::endl;
    CadenaJuego cadena = interpolar_unicode(plantilla);
    std::string repr_num_nivel;
    if (num_nivel == std::nullopt) {
        repr_num_nivel = "-";
    } else {
        repr_num_nivel = std::to_string(num_nivel.value().valor);
    }
    LOG(debug) << "repr_num_nivel= " << repr_num_nivel;
    return cadena.interpolar_por_clave("num_nivel", repr_num_nivel);
}

std::string construir_resultado() { //
    return interpolar_unicode(RESULTADO_NIVEL_1);
}
