#pragma once

#include "../../modelo/control_pizzas.h"
#include "../componente.h"
#include "../vista_shared.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf {
    class RenderTarget;
}
class Etiqueta;

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

///// EtiquetasPreparadas /////

/*
 * Contiene las etiquetas que muestran las pizzas en area de
 * preparadas.
 */
class EtiquetasPreparadas : public ComponenteConFont {
    using TipoPizza = dominio::TipoPizza;
    using PizzasToLabels = std::map<TipoPizza, std::shared_ptr<Etiqueta>>;

  public:
    PizzasToLabels etiquetas_preparadas;

    EtiquetasPreparadas();
    void setup(const dominio::TiposDePizza &tp_disponibles);
    void actualizar(const PizzasToStrings &vista_preparadas //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

///// EtiquetasPedidos /////

/*
 * Contiene los elementos visuales que muestran los pedidos.
 */
class EtiquetasPedidos : public ComponenteConFont {
    using TipoPizza = dominio::TipoPizza;

  private:
    void _actualizar_vista_pedidos(const modelo::Pedidos &);

  public:
    std::vector<TarjetaPedido> tarjetas_pedidos;

    EtiquetasPedidos();
    void actualizar(const modelo::Pedidos & //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
