#include "demos/demo_nivel.h"
#include "demos/map.h"
#include "demos/min_ex.h"
#include "demos/unicode.h"
#include "demos/visual.h"
#include "demos/visual_textos.h"
#include "juego.h"
#include <cassert>
#include <cstdlib> // Para std::atoi
#include <iostream>

#define APP 0

int main(int argc, char *argv[]) { // fmt
    std::cout << std::endl;
    if (argc > 3) {
        std::cout
            << "Uso: " << argv[0]
            << " <num_app>, donde <num_app> es el número de app que se desea "
               "ejecutar\n  Actualmente disponibles: 0, 1";
        return 1;
    }
    int app;
    if (argc >= 2)
        app = std::atoi(argv[1]);
    else
        app = APP;

    switch (app) {
        case 1:
            return demo_nivel(NumNivel(std::atoi(argv[2])));
            break;
        case 2:
            return demo_visual();
            break;
        case 3:
            return demo_visual_textos();
            break;
        case 4:
            return demo_unicode();
            break;
        case 5:
            return min_example();
            break;
        case 6:
            return demo_map();
            break;

        default:
            assert(app == 0);
            return juego();
            break;
    }
}
