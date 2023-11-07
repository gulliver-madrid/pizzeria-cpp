#pragma once

#include "dominio.h"
#include <cassert>
#include <map>
#include <vector>

struct Encargos;
struct TiempoJuego;

/*
 * Contabiliza el numero de pizzas servidas y preparadas de un determinado tipo
 */
struct Contadores {
    int servidas = 0;
    int preparadas = 0;
};

namespace modelo {
    using PizzasAContadores = std::map<dominio::TipoPizza, Contadores>;
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
    bool cubierto() const;
};

using ContenidoPedido = std::map<dominio::TipoPizza, PedidoTipoPizza>;

/* Pedido completo, puede incluir varios tipos de pizza */
struct Pedido {
    ContenidoPedido contenido;
    bool cubierto = false;
    Pedido(ContenidoPedido &&);
    void evaluar();
    bool incluye(dominio::TipoPizza);
    /* Devuelve true si acepta el servicio */
    bool intentar_servir(dominio::TipoPizza);
};

void evaluar_preparacion(
    Encargos &encargos, modelo::PizzasAContadores &contadores, int maximo,
    const TiempoJuego &tiempo_actual
);

/** Representa el estado de preparacion de las pizzas en un momento concreto */
struct EstadoPreparacionPizzas {
    std::vector<EstadoPreparacionPizzaIndividual> datos;
    EstadoPreparacionPizzas(
        const Encargos &encargos,        //
        const TiempoJuego &tiempo_actual //
    );
};
