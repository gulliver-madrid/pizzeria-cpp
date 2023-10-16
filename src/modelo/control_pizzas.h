#pragma once

#include "../shared.h"
#include "modelo.h"
#include <cassert>
#include <vector>

namespace modelo {
    /* Una lista de pedidos */
    using Pedidos = std::vector<Pedido>;

    /* Establece el sistema de control de la produccion y distribucion de pizzas
     */
    struct ControlPizzas {
      private:
        std::vector<TipoPizza> _tipos_disponibles;

      public:
        PizzasAContadores contadores;
        Pedidos pedidos;
        const EsSistemaEstatico &es_estatico;
        ControlPizzas(Pedidos pedidos_, const EsSistemaEstatico &es_estatico);
        const std::vector<TipoPizza> &get_tipos_disponibles() const;
        void procesar_despacho(const TipoPizza tp);
        int obtener_total_preparadas() const;
        int obtener_total_objetivos() const;
        bool faltan_pedidos_por_cubrir() const;
    };
} // namespace modelo

namespace debug {
    void debug_pedidos(const modelo::Pedidos &pedidos);
}
