#pragma once

#include <map>

class Pedido;
struct Contadores;
struct EstadoPreparacionPizzas;

namespace dominio {
    enum class TipoPizza;
}

namespace modelo {
    using PizzasAContadores = std::map<dominio::TipoPizza, Contadores>;
}
