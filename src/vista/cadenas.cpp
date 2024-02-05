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

/* Considerar es un booleano que indica si debe realizarse la interpolacion. De
 * esa manera el codigo llamante puede encadenar llamadas a interpolar y
 * deshabilitar aquellas que no correspondan.
 */
CadenaJuego &CadenaJuego::interpolar_por_clave(
    const std::string &key, const std::string &value_, bool considerar
) {
    if (considerar) {
        std::string &result = this->value;
        std::string placeholder = "{" + key + "}";
        size_t pos = result.find(placeholder);
        if (pos != std::string::npos) {
            result.replace(pos, placeholder.length(), value_);
        }
    }
    return *this;
}

std::string unir_cadenas(
    const std::vector<std::string> &strings, const std::string &separator //
) {
    std::string result;
    for (size_t i = 0; i < strings.size(); ++i) {
        result += strings[i];
        if (i < strings.size() - 1) {
            result += separator;
        }
    }
    return result;
}
