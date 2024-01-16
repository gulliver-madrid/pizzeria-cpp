#pragma once

#include "../../shared.h"
#include <SFML/Graphics/Color.hpp>
#include <optional>
#include <string>

struct BotonData {
    std::string texto;
    sf::Color color_fondo;
    sf::Color color_texto = sf::Color::White;
};

struct BotonDataConFont {
    BotonData data;
    const OptionalFont &font;
};
