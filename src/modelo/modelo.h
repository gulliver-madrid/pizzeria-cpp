#pragma once

#include "dominio.h"
#include <cassert>
#include <map>
#include <vector>

struct Encargos;
struct Tiempo;

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
};

namespace modelo {
    using PizzasAContadores = std::map<TipoPizza, Contadores>;
}

namespace debug {
    void debug_contadores(const modelo::PizzasAContadores &contadores);
}

/* Parte de un pedido relativa a un tipo de pizza */
struct PedidoTipoPizza {
    int servido = 0;
    int objetivo = 0;
    PedidoTipoPizza(int objetivo);
    PedidoTipoPizza(int servido, int objetivo);
};

/* Pedido completo, puede incluir varios tipos de pizza */
struct Pedido {
    std::map<modelo::TipoPizza, PedidoTipoPizza> contenido;
    bool cubierto = false;
    Pedido(std::map<modelo::TipoPizza, PedidoTipoPizza> contenido);
    void evaluar();
};

void evaluar_preparacion(
    Encargos &encargos, modelo::PizzasAContadores &contadores, int maximo,
    Tiempo tiempo_actual
);

struct EstadoPreparacionPizzas {
    std::vector<EstadoPreparacionPizzaIndividual> datos;
    EstadoPreparacionPizzas(const Encargos &encargos);
};
