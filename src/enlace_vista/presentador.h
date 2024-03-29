#pragma once

#include "../modelo/modelo.h"
#include "../modelo/modelo_shared.h"
#include "../vista/presentaciones.h"
#include "../vista/vista_shared.h"
#include <string>
#include <vector>

namespace presentador {
    namespace impl {
        VistaLinea crea_vista_linea( //
            const dominio::TipoPizza tp, UInt parte, UInt todo
        );
        VistaPedido pedido_to_vista(const Pedido &pedido);
    } // namespace impl

    VistaPedidos crear_presentacion_pedidos( //
        const modelo::Pedidos &pedidos
    );

    PizzasToStrings contadores_to_preparadas( //
        const modelo::PizzasAContadores &
    );
    PresentacionPreparacionPizzas estado_preparacion_pizzas_to_vista( //
        const EstadoPreparacionPizzas &                               //
    );

    VistaBarraEstado crea_vista_barra_estado(
        const sf::Time &tiempo_real, const sf::Time &tiempo_juego
    );

} // namespace presentador
