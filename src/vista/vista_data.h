#pragma once

#include <SFML/Graphics/Color.hpp>

#define TAMANO_INICIAL_VENTANA 1800, 920
#define FPS 60

namespace colores {
    namespace barra_progreso {
        using sf::Color;
        const Color FONDO = {230, 230, 230};
        const Color RELLENO = {255, 140, 0}; // 30, 144, 255
        const Color TEXTO = {0, 0, 0};
    } // namespace barra_progreso
} // namespace colores
