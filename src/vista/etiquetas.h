#pragma once

#include "../modelo/modelo.h"
#include <SFML/Graphics.hpp>

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
};

sf::Text generar_etiqueta_instrucciones(
    const sf::Font &font, const std::string &plantilla_instrucciones,
    int objetivo
);
sf::Text generar_etiqueta_resultado(const sf::Font &font);
