#pragma once

#include "../modelo/modelo.h"
#include "../modelo/modelo_shared.h"
#include "presentaciones.h"
#include "vista_shared.h"
#include <string>
#include <vector>

namespace presentador {

    std::string crea_linea_completitud_pizza(
        const dominio::TipoPizza tp, int parte, int todo
    );

    std::string pedido_to_string(const Pedido &pedido);

    VistaPizzasToStrings contadores_to_preparadas( //
        const modelo::PizzasAContadores &
    );
    std::vector<VistaPreparacionPizza> estado_preparacion_pizzas_to_vista( //
        const EstadoPreparacionPizzas &                                    //
    );

} // namespace presentador
