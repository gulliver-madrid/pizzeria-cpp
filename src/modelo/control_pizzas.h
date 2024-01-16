#pragma once

#include "../shared.h"
#include "modelo.h"
#include <vector>

namespace modelo_info {
    const auto MAXIMO_PIZZAS_EN_PREPARACION = 3;
    const auto MAXIMO_PIZZAS_PREPARADAS = 4;
} // namespace modelo_info

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
        int obtener_total_preparadas() const;
        bool faltan_pedidos_por_cubrir() const;
    };
} // namespace modelo

namespace debug {
    void debug_pedidos(const modelo::Pedidos &pedidos);
}
