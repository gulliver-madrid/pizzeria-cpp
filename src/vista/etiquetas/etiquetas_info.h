#pragma once

#include "../../shared.h"
#include <SFML/Graphics.hpp>
#include <optional>

struct EtiquetasInfo {
  private:
    const sf::Font &font;

  public:
    sf::Text instrucciones;
    sf::Text resultado;
    EtiquetasInfo(const sf::Font &);
    void setup(
        const std::string &instr,   //
        const NumNivel &,           //
        std::optional<int> objetivo //
    );
};
