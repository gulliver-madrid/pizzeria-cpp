#pragma once

#include <map>

struct Contadores;

namespace dominio {
    enum class TipoPizza;
}

namespace modelo {
    using PizzasAContadores = std::map<dominio::TipoPizza, Contadores>;
}
