
#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

namespace medidas {
    constexpr int TAMANO_TEXTO_GRANDE = 32;
} // namespace medidas

struct EstiloTexto {
    const int tamano;
    const sf::Color &color;
};

const auto Vector2f_CERO = sf::Vector2f(0, 0);

sf::Text crearEtiqueta(
    const std::string &texto,                    //
    int tamano_fuente,                           //
    const sf::Color &,                           //
    const sf::Font &,                            //
    const sf::Vector2f &posicion = Vector2f_CERO //

);
sf::Text crearEtiqueta(
    const std::string &texto,                    //
    const EstiloTexto &,                         //
    const sf::Font &,                            //
    const sf::Vector2f &posicion = Vector2f_CERO //

);
