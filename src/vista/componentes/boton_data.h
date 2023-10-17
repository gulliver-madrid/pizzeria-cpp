#pragma once

#include <SFML/Graphics.hpp>

enum class Align { //
    Left,
    Right
};

struct BotonData {
    std::string texto;
    sf::Color color_fondo;
    sf::Color color_texto = sf::Color::White;
};
