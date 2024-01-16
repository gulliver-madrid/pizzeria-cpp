#pragma once

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

/* NewType para el numero de nivel del juego */
struct NumNivel {
    const int valor;
    explicit NumNivel(int v) : valor(v) { //
        assert(valor > 0);
    }
    NumNivel &operator=(const NumNivel &) = delete;
};

class ObjetoConFont {
  protected:
    const OptionalFont &font;

  public:
    ObjetoConFont(const OptionalFont &font) : font(font) {}
};
