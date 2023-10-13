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

using PizzasAContadores = std::map<TipoPizza, Contadores>;

void debug_contadores(const PizzasAContadores &contadores);

/* Parte de un pedido relativa a un tipo de pizza */
struct PedidoTipoPizza {
    int servido = 0;
    int objetivo = 0;
    PedidoTipoPizza(int objetivo) : objetivo(objetivo) {
        assert(objetivo >= 0);
    }
    PedidoTipoPizza(int servido, int objetivo)
        : servido(servido), objetivo(objetivo) {
        assert(objetivo >= 0);
        assert(servido >= 0);
        assert(servido <= objetivo);
    }
};

/* Pedido completo, puede incluir varios tipos de pizza */
struct Pedido {
    std::map<TipoPizza, PedidoTipoPizza> contenido;
    bool cubierto = false;
    Pedido(std::map<TipoPizza, PedidoTipoPizza> contenido_) {
        contenido = contenido_;
    }
    void evaluar() {
        bool faltan = false;
        for (auto &par : contenido) {
            auto &pedido_tp = par.second;
            if (pedido_tp.servido < pedido_tp.objetivo) {
                faltan = true;
                break;
            }
        }
        if (!faltan) {
            cubierto = true;
        }
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
