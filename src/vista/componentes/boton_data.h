#pragma once

#include <SFML/Graphics.hpp>

struct BotonData {
    std::string texto;
    sf::Color color_fondo;
    sf::Color color_texto = sf::Color::White;
};

struct BotonDataConFont {
    BotonData data;
    const sf::Font &font;
};
