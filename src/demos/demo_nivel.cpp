#include "demo_nivel.h"
#include "../datos_niveles.h"
#include "../nivel.h"
#include "../setup_juego.h"
#include <cassert>
#include <iostream>

int demo_nivel(int indice_nivel) {
    Globales globales;
    Grid grid;
    bool resultado_setup = setup_juego(globales);
    if (!resultado_setup)
        return EXIT_FAILURE;
    if (indice_nivel >= std::size(datos)) {
        std::cout << "No existe el nivel solicitado" << std::endl;
        return EXIT_FAILURE;
    }

    while (true) {
        Estado estado;

        AccionGeneral res =
            nivel(globales, estado, datos[indice_nivel], grid, true);
        if (res == AccionGeneral::Reiniciar) {
            continue;
        } else {
            assert(res == AccionGeneral::Salir);
            break;
        }
    }

    return 0;
}
