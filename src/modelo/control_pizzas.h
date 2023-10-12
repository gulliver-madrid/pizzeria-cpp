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
    void procesar_despacho(const TipoPizza tp);
    int obtener_total_preparadas() const;
    int obtener_total_objetivos(Pedido &pedido) const;
    bool faltan_pedidos_por_cubrir() const;
};
