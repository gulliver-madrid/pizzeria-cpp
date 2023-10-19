#include "demos/demo_nivel.h"
#include "demos/map.h"
#include "demos/min_ex.h"
#include "demos/prueba.h"
#include "demos/unicode.h"
#include "demos/visual.h"
#include "demos/visual_textos.h"
#include "juego.h"
#include <cassert>
#include <iostream>

#define USER_ERROR 1

enum class AppNombrada {
    Juego,
    Nivel,
    Visual,
    Textos,
    Unicode,
    MinEx,
    Map,
    Prueba,
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
    {"prueba", AppNombrada::Prueba},   //
};

AppNombrada convertir_a_app_nombrada(const char *const nombre_app) {
    AppNombrada app_nombrada;
    if (cadena_to_app_nombrada.count(nombre_app)) {
        app_nombrada = cadena_to_app_nombrada.at(nombre_app);
    } else {
        app_nombrada = AppNombrada::Default;
    }
    return app_nombrada;
}

void write_line(const std::string &s = "") { //
    std::cout << s << std::endl;
}

int main(int argc, char *argv[]) {
    write_line();
    if (argc > 3) {
        write_line("Demasiados argumentos");
        return USER_ERROR;
    }

    const auto primer_arg = argc > 1 ? argv[1] : "";
    const AppNombrada app_nombrada = convertir_a_app_nombrada(primer_arg);
    switch (app_nombrada) {
        case AppNombrada::Juego:
            return juego();
            break;
        case AppNombrada::Nivel:
            {
                int num_nivel_introducido;
                try {
                    num_nivel_introducido = std::stoi(argc > 2 ? argv[2] : "");
                } catch (std::invalid_argument) {
                    write_line("Debe introducirse un número de nivel (un "
                               "entero positivo)");
                    return USER_ERROR;
                }
                if (num_nivel_introducido <= 0) {
                    write_line("El número de nivel debe ser mayor que 0");
                    return USER_ERROR;
                }
                NumNivel num_nivel(num_nivel_introducido);
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
        case AppNombrada::Prueba:
            return demo_prueba();
            break;
        default:
            write_line("Argumentos desconocidos");
            break;
    }
}
