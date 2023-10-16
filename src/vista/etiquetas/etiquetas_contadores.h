#pragma once

#include "../../general.h"
#include <SFML/Graphics.hpp>

using modelo::TipoPizza;

struct EtiquetasContadores {
  private:
    const sf::Font &font;
    // Indica si el sistema de pedidos es estatico
    const EsSistemaEstatico &es_estatico;

    void _actualizar_pedidos_dinamicos(const modelo::Pedidos &pedidos);
    void _actualizar_pedido_estatico(
        const modelo::PizzasAContadores &pizzas_a_contadores, //
        const modelo::Pedidos &pedidos                        //
    );

  public:
    std::map<TipoPizza, sf::Text> texto_preparadas;
    std::map<TipoPizza, sf::Text> texto_servidas;
    std::vector<sf::Text> texto_pedidos;
    EtiquetasContadores(
        const EsSistemaEstatico &es_estatico, const sf::Font &font
    )
        : es_estatico(es_estatico), font(font) {}
    void setup(const std::vector<TipoPizza> &tp_disponibles);
    void actualizar(
        const modelo::PizzasAContadores &pizzas_a_contadores, //
        const modelo::Pedidos &pedidos                        //
    );
    void dibujar(sf::RenderWindow &ventana) const;
};
