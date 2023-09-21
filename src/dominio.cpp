#include "dominio.h"

TipoPizza tipos_de_pizza[] = {TIPOS_DE_PIZZA};

std::unordered_map<TipoPizza, std::string> tipo_pizza_to_string = {
    {TipoPizza::Margarita, "Margarita"},
    {TipoPizza::Pepperoni, "Pepperoni"},
    {TipoPizza::CuatroQuesos, "Cuatro Quesos"},
};
