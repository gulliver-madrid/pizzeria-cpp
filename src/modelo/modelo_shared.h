#pragma once

#include <map>

struct Contadores;
struct EstadoPreparacionPizzas;
struct Pedido;

namespace dominio {
    enum class TipoPizza;
}

namespace modelo {
    using PizzasAContadores = std::map<dominio::TipoPizza, Contadores>;
}
