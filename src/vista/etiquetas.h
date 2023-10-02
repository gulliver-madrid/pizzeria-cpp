#pragma once

#include "../general.h"
#include <SFML/Graphics.hpp>

struct Globales;

struct EtiquetasContadores {
    std::map<TipoPizza, sf::Text> texto_servidas;
    std::map<TipoPizza, sf::Text> texto_preparadas;
    void
    setup(const sf::Font &font, const std::vector<TipoPizza> &tp_disponibles);
    void actualizar(
        const PizzasAContadores &pizzas_a_contadores,
        std::optional<Pedido> &control_pizzas_estatico, bool es_estatico = true
    );
    void dibujar(sf::RenderWindow &ventana) const;
};

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

struct EtiquetasGenerales {
    EtiquetasContadores contadores;
    EtiquetasInfo info;

    void setup(
        const Globales &globales,                    //
        const std::string &instr,                    //
        int num_nivel,                               //
        const std::vector<TipoPizza> tp_disponibles, //
        int total_objetivos
    );
};

sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, sf::Vector2i posicion_panel, const std::string &texto
);
