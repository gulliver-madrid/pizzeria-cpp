#pragma once

#include "../../modelo/control_pizzas.h"
#include "../componentes/componente.h"
#include "../vista_shared.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Etiqueta;

/*
 * Contiene las etiquetas que muestran las pizzas en area de
 * preparadas.
 */
class EtiquetasPreparadas : public ComponenteConFont {
    using TipoPizza = dominio::TipoPizza;
    using PizzasToLabels = std::map<TipoPizza, std::shared_ptr<Etiqueta>>;

  public:
    PizzasToLabels etiquetas_preparadas;

    EtiquetasPreparadas(const dominio::TiposDePizza &tp_disponibles);

    void actualizar(const PizzasToStrings &info_preparadas);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
