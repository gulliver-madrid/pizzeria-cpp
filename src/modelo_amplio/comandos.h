#pragma once

#include "../modelo/dominio.h"
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

    using ComandoData = std::variant<
        Empezar, Salir, AlternarGrid, Reiniciar, Encargar, Despachar>;
    ComandoData comando_data;

    Comando(Empezar cmd) : comando_data(cmd) {}
    Comando(Salir cmd) : comando_data(cmd) {}
    Comando(AlternarGrid cmd) : comando_data(cmd) {}
    Comando(Reiniciar cmd) : comando_data(cmd) {}
    Comando(Encargar cmd) : comando_data(cmd) {}
    Comando(Despachar cmd) : comando_data(cmd) {}
};
