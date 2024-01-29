#pragma once

#include "../modelo/modelo.h"
#include "../modelo/modelo_shared.h"
#include "presentaciones.h"
#include "vista_shared.h"
#include <string>
#include <vector>

namespace presentador {
    namespace impl {
        std::string crea_linea_completitud_pizza(
            const dominio::TipoPizza tp, UInt parte, UInt todo
        );
        std::string pedido_to_string(const Pedido &pedido);
    } // namespace impl

    std::vector<std::pair<std::string, size_t>>
    crear_presentacion_pedidos(const modelo::Pedidos &pedidos //
    );

    PizzasToStrings contadores_to_preparadas( //
        const modelo::PizzasAContadores &
    );
    std::vector<VistaPreparacionPizza> estado_preparacion_pizzas_to_vista( //
        const EstadoPreparacionPizzas &                                    //
    );

    std::string crea_texto_etiqueta_barra_estado(
        const sf::Time &tiempo_real, const sf::Time &tiempo_juego
    );

} // namespace presentador
