#pragma once

#include "../../shared.h"
#include <SFML/Graphics.hpp>

struct EtiquetasInfo {
  private:
    const sf::Font &font;

  public:
    sf::Text instrucciones;
    sf::Text resultado;
    EtiquetasInfo(const sf::Font &);
    void setup(
        const std::string &instr, //
        const NumNivel &,         //
        int total_objetivos       //
    );
};
