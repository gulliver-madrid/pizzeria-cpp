#include "demos/demo_nivel.h"
#include "demos/map.h"
#include "demos/min_ex.h"
#include "demos/unicode.h"
#include "demos/visual.h"
#include "demos/visual_textos.h"
#include "juego.h"
#include <cassert>
#include <iostream>

enum class AppNombrada {
    Juego,
    Nivel,
    Visual,
    Textos,
    Unicode,
    MinEx,
    Map,
    Default
};

const std::map<std::string, AppNombrada> cadena_to_app_nombrada = {
    {"", AppNombrada::Juego},          //
    {"nivel", AppNombrada::Nivel},     //
    {"visual", AppNombrada::Visual},   //
    {"textos", AppNombrada::Textos},   //
    {"unicode", AppNombrada::Unicode}, //
    {"minex", AppNombrada::MinEx},     //
    {"map", AppNombrada::Map},         //
};

int main(int argc, char *argv[]) { //
    std::cout << std::endl;
    if (argc > 3) {
        std::cout << "Demasiados argumentos" << std::endl;
        return 1;
    }

    const auto primer_arg = argc > 1 ? argv[1] : "";
    AppNombrada app_nombrada;
    if (cadena_to_app_nombrada.count(primer_arg)) {
        app_nombrada = cadena_to_app_nombrada.at(primer_arg);
    } else {
        app_nombrada = AppNombrada::Default;
    }
    switch (app_nombrada) {
        case AppNombrada::Juego:
            return juego();
            break;
        case AppNombrada::Nivel:
            {
                const NumNivel num_nivel(std::stoi(argv[2]));
                return demo_nivel(num_nivel);
            }
            break;
        case AppNombrada::Visual:
            return demo_visual();
            break;
        case AppNombrada::Textos:
            return demo_visual_textos();
            break;
        case AppNombrada::Unicode:
            return demo_unicode();
            break;
        case AppNombrada::MinEx:
            return min_example();
            break;
        case AppNombrada::Map:
            return demo_map();
            break;
        default:
            std::cout << "Argumentos desconocidos" << std::endl;
            break;
    }
}
