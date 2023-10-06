#pragma once

#include "../general.h"
#include <SFML/Graphics.hpp>

struct Globales;

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

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

/* Agrupa las etiquetas principales para un nivel determinado */
struct EtiquetasGenerales {
  private:
    const sf::Font &font;

  public:
    EtiquetasContadores contadores;
    EtiquetasInfo info;
    EtiquetasGenerales(bool es_estatico, const sf::Font &font)
        : font(font), contadores(es_estatico, font) {}

    void setup(
        const std::string &instr,                     //
        int num_nivel,                                //
        const std::vector<TipoPizza> &tp_disponibles, //
        int total_objetivos
    );
};

sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, const sf::Vector2f &posicion_panel,
    const std::string &texto
);
