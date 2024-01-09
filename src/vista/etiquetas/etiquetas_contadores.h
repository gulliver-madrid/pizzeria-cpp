#pragma once

#include "../../modelo/control_pizzas.h"
#include "../vista_shared.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf {
    class RenderTarget;
}

///// PedidoCard /////

class PedidoCard : public sf::Drawable {
  public:
    sf::Text label;
    sf::RectangleShape shape;

    PedidoCard(sf::Text label, sf::RectangleShape shape)
        : label(label), shape(shape) {}

    void setPosition(float pos_x, float pos_y);

    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override {
        target.draw(shape);
        target.draw(label);
    }
};

///// EtiquetasContadores /////

struct EtiquetasContadores : public ObjetoConFont, public sf::Drawable {
    using TipoPizza = dominio::TipoPizza;

  private:
    void _actualizar_pedidos_dinamicos(const modelo::Pedidos &);

  public:
    std::map<TipoPizza, sf::Text> etiquetas_preparadas;
    std::map<TipoPizza, sf::Text> etiquetas_servidas;
    std::vector<PedidoCard> cards_pedidos;

    EtiquetasContadores(const sf::Font &);
    void setup(const dominio::TiposDePizza &tp_disponibles);
    void actualizar(
        const VistaPizzasToStrings &vista_preparadas, //
        const modelo::Pedidos &                       //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
