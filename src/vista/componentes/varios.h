
#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

struct EstiloTexto {
    const int tamano;
    const sf::Color &color;
};

struct EstiloTextoConFuente {
    const EstiloTexto &estilo;
    const sf::Font &font;
};

const auto VECTOR_CERO = sf::Vector2f(0, 0);

sf::Text crearEtiqueta(
    int, const sf::Font &, const sf::Color &,
    const sf::Vector2f &posicion = VECTOR_CERO
);
sf::Text crearEtiqueta(
    const EstiloTextoConFuente &fuente_texto,
    const sf::Vector2f &posicion = VECTOR_CERO
);
