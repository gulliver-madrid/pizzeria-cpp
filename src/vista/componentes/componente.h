#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>

enum class Align { //
    Left,
    Right
};

class Componente : public sf::Drawable {
  public:
    void virtual establecer_contenedor(const sf::FloatRect &) = 0;
};
