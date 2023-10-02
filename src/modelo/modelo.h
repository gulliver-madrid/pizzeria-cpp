#pragma once

#include "dominio.h"
#include <map>
#include <vector>

struct Encargos;
struct Tiempo;

struct Contadores {
    int servidas = 0;
    int preparadas = 0;
};

using PizzasAContadores = std::map<TipoPizza, Contadores>;

void debug_contadores(const PizzasAContadores &contadores);

/* Parte de un pedido relativa a un tipo de pizza */
struct PedidoTipoPizza {
    int objetivo = 0;
    int servido = 0;
};

/* Pedido completo, puede incluir varios tipos de pizza */
struct Pedido {
    std::map<TipoPizza, PedidoTipoPizza> contenido;
    bool cubierto = false;
    Pedido(std::map<TipoPizza, PedidoTipoPizza> contenido_) {
        contenido = contenido_;
    }
};

void evaluar_preparacion(
    Encargos &encargos, PizzasAContadores &contadores, int maximo,
    Tiempo tiempo_actual
);

struct EstadoPreparacionPizzas {
    std::vector<EstadoPreparacionPizzaIndividual> datos;
    EstadoPreparacionPizzas(const Encargos &encargos);
};
