#pragma once

#include "dominio.h"
#include "tiempo.h"

enum EstadoJuego {
    MostrandoInstrucciones,
    Activo,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
};

struct EncargoACocina {
    TipoPizza tipo;
    TiempoPreparacion tiempo_preparacion;
};

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
    int objetivo = 0;
};

int encargadas_del_tipo(
    std::vector<EncargoACocina> &encargadas, TipoPizza tipo
);

struct Estado {
    EstadoJuego actual = MostrandoInstrucciones;
    std::map<TipoPizza, Contadores> contadores;
    std::vector<EncargoACocina> encargadas;
};

void evaluar_preparacion(
    std::vector<EncargoACocina> &encargos,
    std::map<TipoPizza, Contadores> &contadores, int maximo,
    Tiempo tiempo_actual
);

int juego();
