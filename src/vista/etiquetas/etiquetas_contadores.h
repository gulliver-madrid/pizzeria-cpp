#pragma once

#include "../../general.h"
#include "../../modelo/control_pizzas.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf {
    class RenderWindow;
}

///// PedidoCard /////

class PedidoCard : public sf::Drawable {
  public:
    sf::Text label;
    sf::RectangleShape shape;

    PedidoCard(sf::Text label, sf::RectangleShape shape)
        : label(label), shape(shape) {}

    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override {
        target.draw(shape);
        target.draw(label);
    }
};

///// EtiquetasContadores /////

struct EtiquetasContadores : public ObjetoConFont {
    using TipoPizza = dominio::TipoPizza;

  private:
    // Indica si el sistema de pedidos es estatico
    const EsSistemaEstatico &es_estatico;

    void _actualizar_pedido_estatico(
        const modelo::PizzasAContadores &, //
        const modelo::Pedidos &            //
    );
    void _actualizar_pedidos_dinamicos(const modelo::Pedidos &);

  public:
    std::map<TipoPizza, sf::Text> etiquetas_preparadas;
    std::map<TipoPizza, sf::Text> etiquetas_servidas;
    std::vector<PedidoCard> cards_pedidos;

    EtiquetasContadores(const EsSistemaEstatico &, const sf::Font &);
    void setup(const dominio::TiposDePizza &tp_disponibles);
    void actualizar(
        const modelo::PizzasAContadores &, //
        const modelo::Pedidos &            //
    );
    void dibujar(sf::RenderWindow &ventana) const;
};
