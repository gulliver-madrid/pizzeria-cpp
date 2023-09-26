#pragma once

#include "nivel.h"
#include <vector>

#define TITLE "Pizzer%ia"

PedidosEstaticos construir_pedidos(std::vector<DatosNivelTipoPizza> datos);

bool setup_juego(Globales &globales);
