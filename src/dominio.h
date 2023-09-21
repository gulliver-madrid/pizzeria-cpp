#pragma once

#include <string>
#include <unordered_map>

enum TipoPizza { Margarita, Pepperoni };

std::unordered_map<TipoPizza, std::string> tipo_pizza_to_string = {
    {TipoPizza::Margarita, "Margarita"},
    {TipoPizza::Pepperoni, "Pepperoni"},
};
