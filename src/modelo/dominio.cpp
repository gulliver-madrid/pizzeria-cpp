#include "dominio.h"
#include "../templates/helpers.h"

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

std::string dominio::to_string(TipoPizza tp) {
    const auto default_value = std::string("tipo de pizza desconocido");
    return get_or(tipo_pizza_to_string, tp, default_value);
}
