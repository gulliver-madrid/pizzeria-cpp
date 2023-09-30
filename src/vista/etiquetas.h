#pragma once

#include "../general.h"
#include <SFML/Graphics.hpp>

struct Globales;

struct EtiquetasContadores {
    std::map<TipoPizza, sf::Text> texto_servidas;
    std::map<TipoPizza, sf::Text> texto_preparadas;
    void setup(sf::Font &font);
    void actualizar(const PizzasAContadores &pizzas_a_contadores);
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
        Globales &globales, const DatosNivel &datos_nivel, int total_objetivos
    );
};

sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, sf::Vector2i posicion_panel, const std::string &texto
);
