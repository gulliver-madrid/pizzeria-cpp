#pragma once

#include "shared_num_nivel.h"
#include <cassert>
#include <memory>

namespace sf {
    class Font;
}

class OptionalFont {
  private:
    std::shared_ptr<sf::Font> font_ptr;

  public:
    void set_pointer(std::shared_ptr<sf::Font> ptr);
    std::shared_ptr<sf::Font> get_pointer() const;
    bool exists() const;
};

constexpr bool MODO_DESARROLLO = true;

class ObjetoConFont {
  protected:
    const OptionalFont &font;

  public:
    ObjetoConFont(const OptionalFont &font) : font(font) {}
};
