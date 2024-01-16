#include "textos.h"
#include "vista/cadenas.h"
#include <iostream>

#define RESULTADO_NIVEL_1                                                      \
    "%!Enhorabuena! Todos los clientes est%an satisfechos."

std::string construir_texto_instrucciones(
    const std::string &plantilla,             //
    const std::shared_ptr<NumNivel> num_nivel //
) {
    std::cout << "En construir_texto_instrucciones()" << std::endl;
    CadenaJuego cadena = interpolar_unicode(plantilla);
    int valor_num_nivel;
    if (num_nivel == nullptr) {
        valor_num_nivel = 0;
    } else {
        valor_num_nivel = num_nivel->valor;
    }
    std::cout << "valor_num_nivel: " << valor_num_nivel << std::endl;
    return cadena.interpolar_por_clave(
        "num_nivel", std::to_string(valor_num_nivel)
    );
}

std::string construir_resultado() { //
    return interpolar_unicode(RESULTADO_NIVEL_1);
}
