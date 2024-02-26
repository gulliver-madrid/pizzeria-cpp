#include "num_nivel.h"
#include <cassert>
#include <stdexcept>

NumNivel::NumNivel(int v) : valor(v) { //
    if (valor <= 0) {
        throw std::invalid_argument("El numero de nivel debe ser mayor que 0");
    };
}
std::string NumNivel::to_string() const { //
    if (!valor)
        return "-";
    return std::to_string(valor);
}
int NumNivel::get_valor() const { //
    return valor;
}

std::string to_string(NumNivelOpcional opt_num_nivel) { //
    if (!opt_num_nivel.has_value())
        return "-";
    return opt_num_nivel.value().to_string();
}
