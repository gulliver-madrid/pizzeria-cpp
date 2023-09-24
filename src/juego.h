#pragma once

#include "modelo/dominio.h"
#include "modelo/modelo.h"
#include "tiempo.h"

enum EstadoJuego {
    MostrandoInstrucciones,
    Activo,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
};

struct Estado {
    EstadoJuego actual = MostrandoInstrucciones;
    std::map<TipoPizza, Contadores> contadores;
    std::vector<EncargoACocina> encargadas;
};

int juego();
