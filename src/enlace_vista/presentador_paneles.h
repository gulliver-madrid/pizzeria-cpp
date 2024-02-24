#pragma once

#include "../modelo/modelo.h"
#include "../modelo/modelo_interno.h"
#include "presentador.h"

class PresentadorPaneles {
  public:
    const ModeloInterno &modelo;

    PresentacionPreparacionPizzas obtener_vista_preparacion() {
        const auto preparacion = modelo.obtener_estado_preparacion_pizzas();
        return presentador::estado_preparacion_pizzas_to_vista(preparacion);
    }

    PizzasToStrings obtener_vista_preparadas() {
        const modelo::PizzasAContadores &contadores =
            modelo.control_pizzas.contadores;
        return presentador::contadores_to_preparadas(contadores);
    }

    PresentacionPedidos obtener_presentacion_pedidos() {
        const auto &pedidos = modelo.control_pizzas.pedidos;
        const auto presentacion_pedidos =
            presentador::crear_presentacion_pedidos(pedidos);
        return presentacion_pedidos;
    }
};
