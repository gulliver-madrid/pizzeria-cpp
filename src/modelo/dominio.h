#pragma once

#include <map>
#include <string>
#include <vector>

// PIZZA_TYPES es una macro que toma otra macro (OP) como argumento
#define PIZZA_TYPES(OP)                                                        \
    OP(Margarita)                                                              \
    OP(Pepperoni)                                                              \
    OP(CuatroQuesos)                                                           \
    OP(Funghi)                                                                 \
    OP(Vegetariana)

namespace dominio {
    enum class TipoPizza {
#define ENUM_OP(pizza) pizza,
        PIZZA_TYPES(ENUM_OP)
#undef ENUM_OP
    };
} // namespace dominio

#define COUNT_OP(pizza) +1
constexpr size_t NUMERO_DE_TIPOS_DE_PIZZA = 0 PIZZA_TYPES(COUNT_OP);
#undef COUNT_OP

namespace dominio {
    extern TipoPizza tipos_de_pizza[NUMERO_DE_TIPOS_DE_PIZZA];
    using TiposDePizza = std::vector<dominio::TipoPizza>;
} // namespace dominio

extern const std::map<dominio::TipoPizza, std::string> tipo_pizza_to_string;

struct EstadoPreparacionPizzaIndividual {
    int porcentaje;
    dominio::TipoPizza tipo;
};

namespace dominio {
    std::string to_string(TipoPizza tp);
} // namespace dominio
