#include "cadenas.h"
#include <map>
#include <sstream>

#define A_ACUTE "\u00E1"
#define E_ACUTE "\u00E9"
#define I_ACUTE "\u00ED"
#define O_ACUTE "\u00F3"
#define U_ACUTE "\u00FA"
#define N_TILDE "\u00F1"
#define START_EXCLAMATION "\u00A1"
#define START_QUESTION "\u00BF"

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

std::string interpolar(std::string plantilla) {
    while (true) {
        std::string prev = plantilla;

        for (const auto &par : reemplazos) {
            size_t posicion;
            while ((posicion = plantilla.find(par.first)) != std::string::npos
            ) {
                plantilla.replace(posicion, 2, par.second);
            }
        }
        if (prev == plantilla) {
            break;
        }
    }
    std::ostringstream oss;
    oss << plantilla;
    return oss.str();
}
