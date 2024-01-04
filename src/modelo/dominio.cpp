#include "dominio.h"

using dominio::TipoPizza;

TipoPizza tipos_de_pizza[] = {
    TipoPizza::Margarita, TipoPizza::Pepperoni,   TipoPizza::CuatroQuesos,
    TipoPizza::Funghi,    TipoPizza::Vegetariana,
};

std::map<TipoPizza, std::string> tipo_pizza_to_string = {
    {TipoPizza::Margarita, "Margarita"},
    {TipoPizza::Pepperoni, "Pepperoni"},
    {TipoPizza::CuatroQuesos, "Cuatro Quesos"},
    {TipoPizza::Funghi, "Funghi"},
    {TipoPizza::Vegetariana, "Vegetariana"},
};
