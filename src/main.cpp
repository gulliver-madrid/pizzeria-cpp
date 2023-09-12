#include "demos/map.h"
#include "demos/visual.h"
#include "juego.h"
#include <cassert>
#include <cstdlib> // Para std::atoi
#include <iostream>

#define APP 0

int main(int argc, char *argv[]) { //
    std::cout << std::endl;
    if (argc > 2) {
        std::cout
            << "Uso: " << argv[0]
            << " <num_app>, donde <num_app> es el número de app que se desea "
               "ejecutar\n  Actualmente disponibles: 0, 1";
        return 1;
    }
    int app;
    if (argc == 2)
        app = std::atoi(argv[1]);
    else
        app = APP;

    switch (app) {
    case 1:
        return demo_map();
        break;
    case 2:
        return demo_visual();
        break;

    default:
        assert(app == 0);
        return juego();
        break;
    }
}
