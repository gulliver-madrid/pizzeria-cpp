#include "juego.h"
#include "cadenas.h"
#include "datos_niveles.h"
#include "globales.h"
#include "nivel.h"
#include "setup_juego.h"
#include "textos.h"
#include "vista/grid.h"
#include <cassert>
#include <unordered_set>

int juego() {
    Globales globales;
    Grid grid;
    bool resultado_setup = setup_juego(globales);
    if (!resultado_setup)
        return EXIT_FAILURE;

    while (true) {
        bool reiniciar = false;
        for (int i = 0; i < NUM_DATOS_NIVELES; i++) {
            bool es_el_ultimo = (i == NUM_DATOS_NIVELES - 1);
            auto res = nivel(globales, datos_niveles[i], grid, es_el_ultimo);
            if (res == AccionGeneral::Reiniciar) {
                reiniciar = true;
                break;
            } else if (res == AccionGeneral::Salir)
                break;
            else {
                assert(res == AccionGeneral::SiguienteNivel);
            }
        }
        if (reiniciar) {
            reiniciar = false;
            continue;
        }
        break;
    }

    return 0;
}
