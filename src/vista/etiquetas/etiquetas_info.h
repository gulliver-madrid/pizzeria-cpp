#pragma once

#include "../../shared.h"
#include <SFML/Graphics/Text.hpp>
#include <optional>

struct EtiquetasInfo : public ObjetoConFont, public sf::Drawable {
  public:
    sf::Text instrucciones;
    sf::Text resultado;
    bool mostrar_instrucciones;
    bool mostrar_resultado;

    EtiquetasInfo(const sf::Font &);
    void setup(
        const std::string &instr, //
        const NumNivel &          //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
    void set_clean();
};
