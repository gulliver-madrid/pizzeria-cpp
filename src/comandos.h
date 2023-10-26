#pragma once

#include "modelo/dominio.h"
#include <variant>

enum class TipoBoton {
    Salir,
    Reiniciar,
    AlternarGrid,
    Empezar,
    Encargar,
    Despachar
};

class Comando {
  public:
    struct Empezar {
        static const TipoBoton tipo() { return TipoBoton::Empezar; }
    };
    struct Salir {
        static const TipoBoton tipo() { return TipoBoton::Salir; }
    };
    struct AlternarGrid {
        static const TipoBoton tipo() { return TipoBoton::AlternarGrid; }
    };
    struct Reiniciar {
        static const TipoBoton tipo() { return TipoBoton::Reiniciar; }
    };
    struct Encargar {
        modelo::TipoPizza tp;
        static const TipoBoton tipo() { return TipoBoton::Encargar; }
    };
    struct Despachar {
        modelo::TipoPizza tp;
        static const TipoBoton tipo() { return TipoBoton::Despachar; }
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
