#pragma once

#include "../../shared.h"
#include <SFML/Graphics/Text.hpp>
#include <optional>

struct EtiquetasInfo : public ObjetoConFont {
  public:
    sf::Text instrucciones;
    sf::Text resultado;
    EtiquetasInfo(const sf::Font &);
    void setup(
        const std::string &instr,                  //
        const NumNivel &,                          //
        const std::optional<int> objetivo_estatico //
    );
};
