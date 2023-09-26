#include "juego.h"
#include "cadenas.h"
#include "manejo_rutas.h"
#include "nivel.h"
#include "paths.h"
#include "textos.h"
#include "vista/grid.h"
#include "vista/vista_data.h"
#include <cassert>
#include <unordered_set>

#define TITLE "Pizzer%ia"

PedidosEstaticos construir_pedidos(std::vector<DatosNivelTipoPizza> datos) {
    std::map<TipoPizza, DatosNivelTipoPizza> pedidos;
    std::unordered_set<TipoPizza> anadidos;
    for (auto dato : datos) {
        assert(anadidos.find(dato.tipo) == anadidos.end());
        pedidos[dato.tipo] = dato;
        anadidos.insert(dato.tipo);
    }
    return {pedidos};
}

// Inicia los elementos del juego que permanecerán entre niveles
// Inicializa las variables globales window, font y buffer
// Devuelve un booleano indicando si se completo con exito
bool setup_juego(Globales &globales) {
    std::string title = TITLE;
    globales.window.create(
        sf::VideoMode(TAMANO_INICIAL_VENTANA), interpolar_unicode(title)
    );
    globales.window.setFramerateLimit(FPS);

    if (!globales.font.loadFromFile(getResourcePath(FONT_PATH).string()))
        return false;

    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(getResourcePath(SUCCESS_SOUND_PATH).string()))
            globales.opt_buffer = buffer;
    }
    return true;
}

int juego() {
    Globales globales;
    Grid grid;
    bool resultado_setup = setup_juego(globales);
    if (!resultado_setup)
        return EXIT_FAILURE;

    DatosNivel datos[] = {
        {INSTRUCCIONES_NIVEL_1, //
         construir_pedidos({
             {

                 DatosNivelTipoPizza{Margarita, 2, 8},
             },
             {

                 DatosNivelTipoPizza{Pepperoni, 0, 4},
             },
             {

                 DatosNivelTipoPizza{CuatroQuesos, 0, 3},
             },
         })},
        {INSTRUCCIONES_NIVEL_2, //
         construir_pedidos({
             {
                 DatosNivelTipoPizza{Margarita, 2, 6},
             },
             {
                 DatosNivelTipoPizza{Pepperoni, 1, 3},
             },
             {
                 DatosNivelTipoPizza{CuatroQuesos, 0, 6},
             },
         })},
    };

    while (true) {
        bool reiniciar = false;
        for (int i = 0; i < std::size(datos); i++) {
            Estado estado;
            bool es_el_ultimo = (i == std::size(datos) - 1);
            bool res = nivel(globales, estado, datos[i], grid, es_el_ultimo);
            if (!res) {
                reiniciar = true;
                break;
            }
        }
        if (reiniciar) {
            continue;
        }
        break;
    }

    return 0;
}
