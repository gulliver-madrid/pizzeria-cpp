#pragma once

#include <string>

#define A_ACUTE "\u00E1"
#define E_ACUTE "\u00E9"
#define I_ACUTE "\u00ED"
#define O_ACUTE "\u00F3"
#define U_ACUTE "\u00FA"
#define N_TILDE "\u00F1"
#define START_EXCLAMATION "\u00A1"
#define START_QUESTION "\u00BF"

std::string interpolar_unicode(std::string plantilla);

struct CadenaJuego {
    std::string value;

    CadenaJuego(const std::string &init_value = "") : value(init_value) {}

    CadenaJuego &interpolar_por_clave(
        const std::string &key,   //
        const std::string &value, //
        bool considerar = true    //
    );

    // Operador para convertir implícitamente a std::string
    operator std::string() const { return value; }
};
