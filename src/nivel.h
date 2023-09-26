#pragma once

#include "general.h"
#include "modelo/modelo.h"
#include "vista/grid.h"

enum FaseNivel {
    MostrandoInstrucciones,
    Activo,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
};

struct Estado {
    FaseNivel actual = MostrandoInstrucciones;
    PizzasAContadores contadores;
    std::vector<EncargoACocina> encargadas;
};

// Datos para un nivel determinado de un tipo concreto de pizza
struct DatosNivelTipoPizza {
    TipoPizza tipo;
    int pizzas_preparadas_iniciales = 0;
    int objetivo_pizzas = 0;
};

struct PedidosEstaticos {
    std::map<TipoPizza, DatosNivelTipoPizza> pizzas;
};

struct DatosNivel {
    std::string instrucciones;
    PedidosEstaticos pedidos;
    DatosNivel(std::string instr, PedidosEstaticos pizzas)
        : instrucciones(instr), pedidos(pizzas) {}
};

PedidosEstaticos construir_pedidos(std::vector<DatosNivelTipoPizza> datos);

bool nivel(                  //
    Globales &globales,      //
    Estado &estado,          //
    DatosNivel &datos_nivel, //
    Grid &grid,              //
    bool es_el_ultimo
);
