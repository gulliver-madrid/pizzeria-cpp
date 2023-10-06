#pragma once

#include <cassert>

/* NewType para el número de nivel del juego */
struct NumNivel {
    int valor;
    explicit NumNivel(int v) : valor(v) { //
        assert(valor > 0);
    }
};
