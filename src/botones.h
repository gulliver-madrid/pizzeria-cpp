#pragma once

#include "componentes.h"

BotonConTexto crearBotonConTexto(
    const std::string &, const sf::Color &color_fondo, const sf::Vector2i &,
    const sf::Font &, const sf::Color &color_texto = sf::Color::White,
    float escala = 1
);

struct Botones {
    BotonConTexto empezar;
    BotonConTexto encargar_margarita;
    BotonConTexto despachar;
    BotonConTexto reiniciar;
    BotonConTexto salir;
    std::vector<BotonConTexto *> todos;

    Botones(sf::Font &);
    void dibujar(sf::RenderWindow &ventana);
};
