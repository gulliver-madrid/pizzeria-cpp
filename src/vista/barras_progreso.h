#pragma once

#include "componentes/barra_progreso.h"
#include "presentaciones.h"
#include "vista_shared.h"
#include <memory>
#include <vector>

struct EstadoPreparacionPizzas;
// TODO: usar forward declaration para BarraProgreso...
std::vector<std::shared_ptr<BarraProgresoConNombre>> crear_barras_progreso( //
    const PresentacionPreparacionPizzas &,                                  //
    const sf::Vector2f &pos_panel                                           //
);
