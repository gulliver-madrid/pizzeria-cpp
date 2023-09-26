#include "cadenas.h"
#include <map>
#include <sstream>

const std::map<std::string, std::string> reemplazos = {
    {"%a", A_ACUTE},           //
    {"%i", I_ACUTE},           //
    {"%e", E_ACUTE},           //
    {"%o", O_ACUTE},           //
    {"%u", U_ACUTE},           //
    {"%n", N_TILDE},           //
    {"%?", START_QUESTION},    //
    {"%!", START_EXCLAMATION}, //
};

std::string interpolar_unicode(const std::string plantilla) {
    std::string nueva = plantilla;
    while (true) {
        std::string prev = nueva;

        for (const auto &par : reemplazos) {
            size_t posicion;
            while ((posicion = nueva.find(par.first)) != std::string::npos) {
                nueva.replace(posicion, 2, par.second);
            }
        }
        if (prev == nueva) {
            break;
        }
    }
    std::ostringstream oss;
    oss << nueva;
    return oss.str();
}

CadenaJuego &CadenaJuego::interpolar_por_clave(
    const std::string &key, const std::string &value
) {
    std::string &result = this->value;
    std::string placeholder = "{" + key + "}";
    size_t pos = result.find(placeholder);
    if (pos != std::string::npos) {
        result.replace(pos, placeholder.length(), value);
    }

    return *this;
}
