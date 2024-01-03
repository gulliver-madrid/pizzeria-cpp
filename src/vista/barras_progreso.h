#pragma once

#include "componentes/barra_progreso.h"

struct EstadoPreparacionPizzas;

std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, const sf::Vector2f &pos_panel,
    const sf::Font &font
);
