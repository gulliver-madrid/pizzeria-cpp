#pragma once

#include "dominio.h"
#include "modelo_shared.h"
#include <cassert>
#include <map>
#include <vector>

namespace sf {
    class Time;
} // namespace sf
struct Encargos;

/*
 * Contabiliza el numero de pizzas servidas y preparadas de un determinado tipo.
 * Una vez servidas se descuentan de las preparadas.
 * # TODO: crear un unico constructor y metodos explicitos para evitar
 * confusion entre preparadas y servidas.
 */
struct Contadores {
    int servidas = 0;
    // Actualmente en el area de preparadas
    int preparadas = 0;
};

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
class Pedido {
    bool cubierto = false;

  public:
    ContenidoPedido contenido;
    Pedido(ContenidoPedido &&);
    void evaluar();
    bool incluye(dominio::TipoPizza) const;
    /* Devuelve true si acepta el servicio */
    bool esta_cubierto() const;
    bool intentar_servir(dominio::TipoPizza);
};

void evaluar_preparacion(
    Encargos &encargos, modelo::PizzasAContadores &contadores, int maximo,
    const sf::Time &tiempo_actual
);

/** Representa el estado de preparacion de las pizzas en un momento concreto */
struct EstadoPreparacionPizzas {
    std::vector<EstadoPreparacionPizzaIndividual> datos;
    EstadoPreparacionPizzas(
        const Encargos &encargos,     //
        const sf::Time &tiempo_actual //
    );
};
