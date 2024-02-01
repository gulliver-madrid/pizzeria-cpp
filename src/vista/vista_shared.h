#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

class BotonConTexto;

namespace dominio {
    enum class TipoPizza;
    using TiposDePizza = std::vector<TipoPizza>;
} // namespace dominio

// TODO:nombres mas descriptivo para distinguir los nombres de las pizzas de la
// presentacion preparadas,
using PizzasToStrings = std::map<dominio::TipoPizza, std::string>;
using TipoPizzaToBoton =
    std::map<dominio::TipoPizza, std::shared_ptr<BotonConTexto>>;
using Botones = std::vector<std::shared_ptr<BotonConTexto>>;
using PresentacionPedidos = std::vector<std::pair<std::string, size_t>>;
