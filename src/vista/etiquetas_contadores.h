#pragma once

#include "../general.h"
#include <SFML/Graphics.hpp>

struct EtiquetasContadores {
  private:
    const sf::Font &font;
    // Indica si el sistema de pedidos es estatico
    const bool es_estatico;

    void _actualizar_pedidos_dinamicos(const Pedidos &pedidos);
    void _actualizar_pedido_estatico(
        const PizzasAContadores &pizzas_a_contadores, //
        const Pedidos &pedidos                        //
    );

  public:
    std::map<TipoPizza, sf::Text> texto_preparadas;
    std::map<TipoPizza, sf::Text> texto_servidas;
    std::vector<sf::Text> texto_pedidos;
    EtiquetasContadores(bool es_estatico, const sf::Font &font)
        : es_estatico(es_estatico), font(font) {}
    void setup(const std::vector<TipoPizza> &tp_disponibles);
    void actualizar(
        const PizzasAContadores &pizzas_a_contadores, //
        const Pedidos &pedidos                        //
    );
    void dibujar(sf::RenderWindow &ventana) const;
};
