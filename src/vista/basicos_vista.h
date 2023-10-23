#pragma once

#include <SFML/Graphics.hpp>

enum class IndicePanel {
    PANEL_ENCARGAR,
    PANEL_EN_PREPARACION,
    PANEL_PREPARADAS,
    PANEL_PEDIDOS,
};

namespace medidas {
    constexpr int ANCHO_PANEL = 390;
    constexpr int ALTO_PANEL = 700;

    // Margenes externos de los paneles
    constexpr int MARGEN_IZQ_PANELES = 50;
    constexpr int MARGEN_TOP_PANELES = 50;

    constexpr int MARGEN_IZQ_ETIQUETAS = 30;
    constexpr int FILA_BOTONES_GENERALES = 800;
    constexpr int FILA_BARRA_ESTADO = FILA_BOTONES_GENERALES;
    constexpr int SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES = 25;

    // Posiciones desde el inicio del panel respectivo
    constexpr int FILA_TITULOS_PANELES = 50;
    constexpr int FILA_CONTENIDO_PANEL = 150;
} // namespace medidas

namespace colores {
    const auto COLOR_FONDO = sf::Color(60, 0, 150);
    const auto TEXTO_INSTRUCCIONES = sf::Color::Yellow;
    const auto TEXTO_RESULTADO = sf::Color(255, 160, 0);
} // namespace colores

namespace basicos_vista {
    sf::Vector2f obtener_posicion_panel(const IndicePanel &indice_panel);
}
