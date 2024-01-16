#pragma once

#include <memory>

constexpr bool MODO_DESARROLLO = true;

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

class ObjetoConFont {
  protected:
    const OptionalFont &font;

  public:
    ObjetoConFont(const OptionalFont &font);
};
