#pragma once

#include <boost/log/trivial.hpp>
#include <cassert>
#include <tuple>
#include <vector>

void init_log();

// Usa un nombre abreviado
#define LOG BOOST_LOG_TRIVIAL

namespace sf {
    class Font;
} // namespace sf

constexpr bool MODO_DESARROLLO = true;

/* NewType para el numero de nivel del juego */
struct NumNivel {
    const int valor;
    explicit NumNivel(int v) : valor(v) { //
        assert(valor > 0);
    }
    NumNivel(const NumNivel &) = delete;
    NumNivel &operator=(const NumNivel &) = delete;
};

class ObjetoConFont {
  protected:
    const sf::Font &font;

  public:
    ObjetoConFont(const sf::Font &font) : font(font) {}
};
