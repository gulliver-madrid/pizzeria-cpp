#pragma once

#include "../modelo/modelo_shared.h"
#include "vista_shared.h"

class Pedido;

namespace presentador {

    std::string crea_linea_completitud_pizza(
        const dominio::TipoPizza tp, int parte, int todo
    );

    std::string pedido_to_string(const Pedido &pedido);

    VistaPizzasToStrings contadores_to_preparadas( //
        const modelo::PizzasAContadores &
    );
} // namespace presentador
