
#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <optional>
#include <string>

namespace sf {
    class Font;
    class Text;
} // namespace sf

namespace medidas {
    constexpr int TAMANO_TEXTO_GRANDE = 32;
} // namespace medidas

struct EstiloTexto {
    const int tamano;
    const sf::Color &color;
};

const auto Vector2f_CERO = sf::Vector2f(0, 0);

sf::Text crearEtiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const OptionalFont &      //
);

sf::Text crearEtiqueta(
    const std::string &texto,                    //
    int tamano_fuente,                           //
    const sf::Color &,                           //
    const OptionalFont &,                        //
    const sf::Vector2f &posicion = Vector2f_CERO //

);
sf::Text crearEtiqueta(
    const std::string &texto,                    //
    const EstiloTexto &,                         //
    const OptionalFont &,                        //
    const sf::Vector2f &posicion = Vector2f_CERO //
);

std::unique_ptr<sf::Text> crear_puntero_a_etiqueta(
    const std::string &texto,    //
    const EstiloTexto &estilo,   //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //
);
