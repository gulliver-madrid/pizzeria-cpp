#pragma once

#include "../../general.h"
#include "../../modelo/control_pizzas.h"
#include <SFML/Graphics.hpp>

struct EtiquetasContadores {
    using TipoPizza = modelo::TipoPizza;

  private:
    const sf::Font &font;
    // Indica si el sistema de pedidos es estatico
    const EsSistemaEstatico &es_estatico;

    void _actualizar_pedidos_dinamicos(const modelo::Pedidos &);
    void _actualizar_pedido_estatico(
        const modelo::PizzasAContadores &, //
        const modelo::Pedidos &            //
    );

  public:
    std::map<TipoPizza, sf::Text> etiquetas_preparadas;
    std::map<TipoPizza, sf::Text> etiquetas_servidas;
    std::vector<sf::Text> etiquetas_pedidos;
    EtiquetasContadores(const EsSistemaEstatico &, const sf::Font &);
    void setup(const modelo::TiposDePizza &tp_disponibles);
    void actualizar(
        const modelo::PizzasAContadores &, //
        const modelo::Pedidos &            //
    );
    void dibujar(sf::RenderWindow &ventana) const;
};
