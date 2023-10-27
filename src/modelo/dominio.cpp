#include "dominio.h"

using dominio::TipoPizza;

TipoPizza tipos_de_pizza[] = {
    TipoPizza::Margarita,
    TipoPizza::Pepperoni,
    TipoPizza::CuatroQuesos,
};

std::map<TipoPizza, std::string> tipo_pizza_to_string = {
    {TipoPizza::Margarita, "Margarita"},
    {TipoPizza::Pepperoni, "Pepperoni"},
    {TipoPizza::CuatroQuesos, "Cuatro Quesos"},
};
