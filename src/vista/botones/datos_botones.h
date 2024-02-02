#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace colores {
    namespace botones_encargar {
        const auto FONDO = sf::Color::Green;
        const auto TEXTO = sf::Color::Black;
    } // namespace botones_encargar
    namespace botones_despachar {
        const auto FONDO = sf::Color::Green;
        const auto TEXTO = sf::Color::Black;
    } // namespace botones_despachar
} // namespace colores

namespace medidas {
    const auto POSICION_BOTON_EMPEZAR = sf::Vector2f(500, 450);
    const auto DIF_VERTICAL_BOTONES_ENCARGAR = 80;
} // namespace medidas
