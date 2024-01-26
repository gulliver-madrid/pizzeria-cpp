#include "juego.h"
#include "datos_niveles.h"
#include "globales.h"
#include "nivel.h"
#include "setup_juego.h"
#include "shared/log_init.h"
#include "textos.h"
#include "vista/grid.h"
#include <cassert>
#include <unordered_set>

int juego() {
    const auto globales = std::make_shared<Globales>();
    const auto grid = std::make_shared<Grid>();
    bool resultado_setup = setup_juego(globales);
    LOG(info) << "resultado_setup: " << resultado_setup << std::endl;
    if (!resultado_setup)
        return EXIT_FAILURE;

    while (true) {
        bool reiniciar = false;
        for (int i = 0; i < NUM_DATOS_NIVELES; i++) {
            bool es_el_ultimo = (i == NUM_DATOS_NIVELES - 1);
            auto num_nivel = NumNivelOpcional(i + 1);
            auto datos_nivel = std::make_shared<DatosNivel>(datos_niveles[i]);
            assert(datos_nivel);
            LOG(info) << "A punto de crear Nivel " << num_nivel.to_string();
            Nivel nivel(globales, datos_nivel, num_nivel, grid, es_el_ultimo);

            auto res = nivel.ejecutar();
            if (res == AccionGeneral::Reiniciar) {
                reiniciar = true;
                break;
            } else if (res == AccionGeneral::Salir) {
                globales->window.close();
                break;
            } else {
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
