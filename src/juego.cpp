#include "juego.h"
#include "cadenas.h"
#include "datos_niveles.h"
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
        for (int i = 0; i < std::size(datos); i++) {
            Estado estado;
            bool es_el_ultimo = (i == std::size(datos) - 1);
            auto res = nivel(globales, estado, datos[i], grid, es_el_ultimo);
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
