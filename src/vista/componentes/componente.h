#pragma once

#include <SFML/Graphics.hpp>

enum class Align { //
    Left,
    Right
};

class Componente {
  public:
    void virtual establecer_rect_padre(const sf::FloatRect &) = 0;
};
