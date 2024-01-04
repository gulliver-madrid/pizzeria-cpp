#include "dominio.h"

using dominio::TipoPizza;

const TipoPizza tipos_de_pizza[] = {
#define ARRAY_OP(pizza) TipoPizza::pizza,
    PIZZA_TYPES(ARRAY_OP)
#undef ARRAY_OP
};

const std::map<TipoPizza, std::string> tipo_pizza_to_string = {
#define MAP_OP(pizza) {TipoPizza::pizza, #pizza},
    PIZZA_TYPES(MAP_OP)
#undef MAP_OP
};
