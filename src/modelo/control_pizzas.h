#pragma once

#include "../shared/font.h"
#include "modelo.h"
#include <vector>

namespace modelo {
    /* Una lista de pedidos */
    using Pedidos = std::vector<Pedido>;

    /* Establece el sistema de control de la produccion y distribucion de pizzas
     */
    struct ControlPizzas {
      private:
        dominio::TiposDePizza _tipos_disponibles;

      public:
        PizzasAContadores contadores;
        Pedidos pedidos;

        void add_pedidos(Pedidos);
        const dominio::TiposDePizza &get_tipos_disponibles() const;
        void procesar_despacho(dominio::TipoPizza tp);
        UInt obtener_total_preparadas() const;
        bool faltan_pedidos_por_cubrir() const;
    };
} // namespace modelo

namespace debug {
    void debug_pedidos(const modelo::Pedidos &pedidos);
}
