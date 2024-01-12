#pragma once

#include "componentes/barra_progreso.h"
#include "presentador.h"
#include <vector>

struct EstadoPreparacionPizzas;

std::vector<BarraProgresoConNombre> crear_barras_progreso( //
    const EstadoPreparacionPizzas &,                       //
    const sf::Vector2f &pos_panel,                         //
    const sf::Font &                                       //
);
