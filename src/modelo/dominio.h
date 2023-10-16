#pragma once

#include <map>
#include <string>

#define TIPOS_DE_PIZZA Margarita, Pepperoni, CuatroQuesos
#define NUMERO_DE_TIPOS_DE_PIZZA 3

namespace modelo {
    enum class TipoPizza { TIPOS_DE_PIZZA };
    extern TipoPizza tipos_de_pizza[NUMERO_DE_TIPOS_DE_PIZZA];
} // namespace modelo

extern std::map<modelo::TipoPizza, std::string> tipo_pizza_to_string;

struct EstadoPreparacionPizzaIndividual {
    int porcentaje;
    modelo::TipoPizza tipo;
};
