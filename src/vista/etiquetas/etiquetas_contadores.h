#pragma once

#include "../../modelo/control_pizzas.h"
#include "../componente.h"
#include "../vista_shared.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf {
    class RenderTarget;
}

///// TarjetaPedido /////

class TarjetaPedido : public sf::Drawable {
  public:
    sf::Text label;
    sf::RectangleShape shape;

    TarjetaPedido(sf::Text label, sf::RectangleShape shape);
    void setPosition(float pos_x, float pos_y);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

///// EtiquetasContadores /////

/*
 * Contiene los elementos visuales que muestran las pizzas en area de
 * preparadas, servidas y los pedidos.
 */
struct EtiquetasContadores : public ComponenteConFont {
    using TipoPizza = dominio::TipoPizza;
    using PizzasToLabels = std::map<TipoPizza, sf::Text>;

  private:
    void _actualizar_vista_pedidos(const modelo::Pedidos &);

  public:
    PizzasToLabels etiquetas_preparadas;
    PizzasToLabels etiquetas_servidas;
    std::vector<TarjetaPedido> tarjetas_pedidos;

    EtiquetasContadores();
    void setup(const dominio::TiposDePizza &tp_disponibles);
    void actualizar(
        const PizzasToStrings &vista_preparadas, //
        const modelo::Pedidos &                  //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
