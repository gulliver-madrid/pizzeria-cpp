#pragma once

#include <map>
#include <string>

namespace dominio {
    enum class TipoPizza;
}

using PizzasToStrings = std::map<dominio::TipoPizza, std::string>;
