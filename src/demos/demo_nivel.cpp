#include "demo_nivel.h"
#include "../datos_niveles.h"
#include "../globales.h"
#include "../nivel.h"
#include "../setup_juego.h"
#include <cassert>
#include <iostream>

int demo_nivel(NumNivel numero_nivel) {

    std::cout << "DEMO NIVEL " << numero_nivel.valor << std::endl;
    int indice_nivel = numero_nivel.valor - 1;
    const auto globales = std::make_shared<Globales>();
    const auto grid = std::make_shared<Grid>();
    bool resultado_setup = setup_juego(globales);
    if (!resultado_setup)
        return EXIT_FAILURE;
    if (indice_nivel >= NUM_DATOS_NIVELES) {
        std::cout << "No existe el nivel solicitado" << std::endl;
        return EXIT_FAILURE;
    }

    while (true) {
        Nivel nivel(
            globales, std::make_shared<DatosNivel>(datos_niveles[indice_nivel]),
            std::optional<NumNivel>(numero_nivel), grid, true
        );
        AccionGeneral res = nivel.ejecutar();
        if (res == AccionGeneral::Reiniciar) {
            continue;
        } else {
            assert(res == AccionGeneral::Salir);
            break;
        }
    }

    return 0;
}
