#pragma once

#include <map>
#include <string>

namespace dominio {
    enum class TipoPizza;
}

using VistaPizzasToStrings = std::map<dominio::TipoPizza, std::string>;
