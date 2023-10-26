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
        modelo::TipoPizza tp;
    };
    struct Despachar {
        modelo::TipoPizza tp;
    };

    using ComandoVar = std::variant<
        Empezar, Salir, AlternarGrid, Reiniciar, Encargar, Despachar>;
    ComandoVar comando;

    Comando(Empezar cmd) : comando(cmd) {}
    Comando(Salir cmd) : comando(cmd) {}
    Comando(AlternarGrid cmd) : comando(cmd) {}
    Comando(Reiniciar cmd) : comando(cmd) {}
    Comando(Encargar cmd) : comando(cmd) {}
    Comando(Despachar cmd) : comando(cmd) {}
};
