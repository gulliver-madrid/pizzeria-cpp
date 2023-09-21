#pragma once

#include <string>
#include <unordered_map>

#define TIPOS_DE_PIZZA Margarita, Pepperoni
#define NUMERO_DE_TIPOS_DE_PIZZA 2

enum TipoPizza { TIPOS_DE_PIZZA };
extern TipoPizza tipos_de_pizza[NUMERO_DE_TIPOS_DE_PIZZA];

extern std::unordered_map<TipoPizza, std::string> tipo_pizza_to_string;

struct PorcentajeConTipoPizza {
    int porcentaje;
    TipoPizza tipo;
};
