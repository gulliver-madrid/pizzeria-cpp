#pragma once

#include <cassert>

constexpr bool MODO_DESARROLLO = true;

/* NewType para el número de nivel del juego */
struct NumNivel {
    const int valor;
    explicit NumNivel(int v) : valor(v) { //
        assert(valor > 0);
    }
    NumNivel(const NumNivel &) = delete;
    NumNivel &operator=(const NumNivel &) = delete;
};

/* NewType para definir si el sistema de tipos es estatico */
struct EsSistemaEstatico {
    const bool valor;
    explicit EsSistemaEstatico(bool v) : valor(v) {}
    EsSistemaEstatico(const EsSistemaEstatico &) = delete;
    EsSistemaEstatico &operator=(const EsSistemaEstatico &) = delete;
};
