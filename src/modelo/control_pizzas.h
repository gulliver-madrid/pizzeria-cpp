#pragma once

#include "../shared.h"
#include "modelo.h"
#include <cassert>
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
        const EsSistemaEstatico &es_estatico;
        ControlPizzas(Pedidos pedidos_, const EsSistemaEstatico &es_estatico);
        const dominio::TiposDePizza &get_tipos_disponibles() const;
        void procesar_despacho(dominio::TipoPizza tp);
        int obtener_total_preparadas() const;
        int obtener_objetivo_total_estatico() const;
        bool faltan_pedidos_por_cubrir() const;
    };
} // namespace modelo

namespace debug {
    void debug_pedidos(const modelo::Pedidos &pedidos);
}
