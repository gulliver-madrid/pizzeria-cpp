#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/Text.hpp>

struct Etiqueta {
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
};
