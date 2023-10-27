#pragma once

#include "modelo/dominio.h"
#include <variant>

class Comando {
  public:
    struct Empezar {};
    struct Salir {};
    struct AlternarGrid {};
    struct Reiniciar {};
    struct Encargar {
        dominio::TipoPizza tp;
    };
    struct Despachar {
        dominio::TipoPizza tp;
    };

    using ComandoVar = std::variant<
        Empezar, Salir, AlternarGrid, Reiniciar, Encargar, Despachar>;
    ComandoVar variante;

    Comando(Empezar cmd) : variante(cmd) {}
    Comando(Salir cmd) : variante(cmd) {}
    Comando(AlternarGrid cmd) : variante(cmd) {}
    Comando(Reiniciar cmd) : variante(cmd) {}
    Comando(Encargar cmd) : variante(cmd) {}
    Comando(Despachar cmd) : variante(cmd) {}
};
