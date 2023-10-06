#pragma once

#include "modelo.h"
#include <cassert>
#include <vector>

/* Una lista de pedidos */
using Pedidos = std::vector<Pedido>;

void debug_pedidos(const Pedidos &pedidos);

/* Establece el sistema de control de la producción y distribución de pizzas */
struct ControlPizzas {
  private:
    std::vector<TipoPizza> _tipos_disponibles;

  public:
    PizzasAContadores contadores;
    Pedidos pedidos;
    bool es_estatico;
    ControlPizzas(Pedidos pedidos_, bool es_estatico_ = true);
    const std::vector<TipoPizza> &get_tipos_disponibles() const;
};
