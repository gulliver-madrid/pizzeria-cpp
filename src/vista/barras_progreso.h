#pragma once

#include "componentes/barra_progreso.h"
#include "presentaciones.h"
#include <memory>
#include <vector>

struct EstadoPreparacionPizzas;

std::vector<std::shared_ptr<BarraProgresoConNombre>> crear_barras_progreso( //
    const VistaPreparacionPizzas &,                                         //
    const sf::Vector2f &pos_panel,                                          //
    const OptionalFont &                                                    //
);
