
#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

struct EstiloTexto {
    const int tamano;
    const sf::Color &color;
};

const auto Vector2f_CERO = sf::Vector2f(0, 0);

sf::Text crearEtiqueta(
    int, const sf::Color &, const sf::Font &,
    const sf::Vector2f &posicion = Vector2f_CERO
);
sf::Text crearEtiqueta(
    const EstiloTexto &estilo, const sf::Font &font,
    const sf::Vector2f &posicion = Vector2f_CERO
);
