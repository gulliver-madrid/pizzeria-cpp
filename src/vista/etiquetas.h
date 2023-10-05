#pragma once

#include "../general.h"
#include <SFML/Graphics.hpp>

struct Globales;

struct EtiquetasContadores {
  private:
    const sf::Font &font;
    void _actualizar_pedidos_dinamicos(const Pedidos &pedidos);
    void _actualizar_pedido_estatico(
        const PizzasAContadores &pizzas_a_contadores, //
        const Pedidos &pedidos                        //
    );

  public:
    std::map<TipoPizza, sf::Text> texto_preparadas;
    std::map<TipoPizza, sf::Text> texto_servidas;
    std::vector<sf::Text> texto_pedidos;
    EtiquetasContadores(const sf::Font &font) : font(font) {}
    void setup(const std::vector<TipoPizza> &tp_disponibles, bool es_estatico);
    void actualizar(
        const PizzasAContadores &pizzas_a_contadores, //
        const Pedidos &pedidos,                       //
        bool es_estatico
    );
    void dibujar(sf::RenderWindow &ventana) const;
};

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

struct EtiquetasGenerales {
    const sf::Font &font;
    EtiquetasContadores contadores;
    EtiquetasInfo info;
    EtiquetasGenerales(const sf::Font &font) : font(font), contadores(font) {}

    void setup(
        const std::string &instr,                     //
        int num_nivel,                                //
        const std::vector<TipoPizza> &tp_disponibles, //
        bool es_estatico,                             //
        int total_objetivos
    );
};

sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, const sf::Vector2f &posicion_panel,
    const std::string &texto
);
