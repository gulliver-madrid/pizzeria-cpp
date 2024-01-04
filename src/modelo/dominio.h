#pragma once

#include <map>
#include <string>
#include <vector>

#define TIPOS_DE_PIZZA Margarita, Pepperoni, CuatroQuesos, Funghi, Vegetariana
#define NUMERO_DE_TIPOS_DE_PIZZA 5

namespace dominio {
    enum class TipoPizza { TIPOS_DE_PIZZA };
    extern TipoPizza tipos_de_pizza[NUMERO_DE_TIPOS_DE_PIZZA];
    using TiposDePizza = std::vector<dominio::TipoPizza>;
} // namespace dominio

extern std::map<dominio::TipoPizza, std::string> tipo_pizza_to_string;

struct EstadoPreparacionPizzaIndividual {
    int porcentaje;
    dominio::TipoPizza tipo;
};
