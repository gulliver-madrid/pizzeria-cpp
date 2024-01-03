#pragma once

#include <SFML/Graphics/Rect.hpp>

enum class Align { //
    Left,
    Right
};

class Componente {
  public:
    void virtual establecer_contenedor(const sf::FloatRect &) = 0;
};
