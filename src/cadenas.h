#pragma once

#include <string>

std::string interpolar_unicode(std::string plantilla);

struct CadenaJuego {
    std::string value;

    CadenaJuego(const std::string &init_value = "") : value(init_value) {}

    CadenaJuego &
    interpolar_por_clave(const std::string &key, const std::string &value);

    // Operador para convertir implícitamente a std::string
    operator std::string() const { return value; }
};
