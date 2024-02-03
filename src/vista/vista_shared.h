#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

class BotonConTexto;
struct VistaPedido;
struct VistaPreparacionPizza;

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

namespace sf {
    class RenderTarget;
}

// presentaciones
using PresentacionPreparacionPizzas = std::vector<VistaPreparacionPizza>;
using PresentacionPedidos = std::vector<VistaPedido>;
