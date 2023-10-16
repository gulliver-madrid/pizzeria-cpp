#pragma once

#include <cassert>

constexpr bool MODO_DESARROLLO = true;

/* NewType para el número de nivel del juego */
struct NumNivel {
    int valor;
    explicit NumNivel(int v) : valor(v) { //
        assert(valor > 0);
    }
    NumNivel(const NumNivel &) = delete;
    NumNivel &operator=(const NumNivel &) = delete;
};
