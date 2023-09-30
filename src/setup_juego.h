#pragma once

#include "general.h"
#include <vector>

#define TITLE "Pizzer%ia"

struct Globales;

PedidosEstaticos
construir_pedidos(const std::vector<DatosNivelTipoPizza> datos_niveles);

bool setup_juego(Globales &globales);
