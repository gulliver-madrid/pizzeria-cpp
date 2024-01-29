#pragma once

#include <map>
#include <vector>

class Pedido;
struct Contadores;
struct EstadoPreparacionPizzas;

namespace dominio {
    enum class TipoPizza;
}

namespace modelo {
    using PizzasAContadores = std::map<dominio::TipoPizza, Contadores>;
    using Pedidos = std::vector<Pedido>;
} // namespace modelo
