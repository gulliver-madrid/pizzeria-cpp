#include "demos/map.h"
#include "juego.h"
#include <cassert>
#include <cstdlib> // Para std::atoi
#include <iostream>

#define APP 0

int main(int argc, char *argv[]) { //
    if (argc > 2) {
        std::cout << "Uso: " << argv[0] << " <app>\n";
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

    default:
        assert(app == 0);
        return juego();
        break;
    }
}
