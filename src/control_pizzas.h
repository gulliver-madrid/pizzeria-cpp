#pragma once

#include "modelo/modelo.h"
#include <cassert>

struct ControlPizzasDinamico {
    // TODO: implementar el control de pedidos cubiertos parcial o totalmente
};

enum class TipoSistemaPedidos { Estatico, Dinamico };

/* Establece el sistema de control de la producción y distribución de pizzas */
struct ControlPizzas {
  private:
    union {
        PizzasAContadores contadores;
        ControlPizzasDinamico control_dinamico;
    };

  public:
    TipoSistemaPedidos tipo;
    ControlPizzas(PizzasAContadores contadores_) : contadores(contadores_) {
        tipo = TipoSistemaPedidos::Estatico;
    }

    ~ControlPizzas() {
        if (tipo == TipoSistemaPedidos::Estatico) {
            contadores.~PizzasAContadores();
        } else {
            control_dinamico.~ControlPizzasDinamico();
        }
    }
    const PizzasAContadores &get_contadores_const() const {
        assert(tipo == TipoSistemaPedidos::Estatico);
        return contadores;
    }
    PizzasAContadores &get_contadores() {
        assert(tipo == TipoSistemaPedidos::Estatico);
        return contadores;
    }
};
