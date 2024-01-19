#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

struct Etiqueta : public sf::Drawable {
    sf::Text etiqueta;
    Etiqueta(
        const std::string &texto, //
        int tamano_fuente,        //
        const OptionalFont &font  //
    ) {
        etiqueta.setString(texto);
        if (font.exists()) {
            etiqueta.setFont(*font.get_pointer());
            etiqueta.setCharacterSize(tamano_fuente);
        };
    }
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override {
        target.draw(etiqueta);
    };
};
