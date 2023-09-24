#pragma once

#include <SFML/Graphics.hpp>

enum IndicePanel {
    PANEL_ENCARGAR,
    PANEL_EN_PREPARACION,
    PANEL_PREPARADAS,
    PANEL_PEDIDOS,
};

namespace medidas {
    constexpr int TAMANO_FUENTE_TITULO_PANELES = 36;
    constexpr int TAMANO_FUENTE_ETIQUETAS = 24;
    constexpr int MARGEN_IZQ_ETIQUETAS = 30;
    constexpr int ANCHO_PANEL = 390;
    constexpr int ALTO_PANEL = 700;
    constexpr int GROSOR_BORDE_PANEL = 3;
    constexpr int FILA_CONTENIDO_PANEL = 200;
    constexpr int MARGEN_TOP_PANELES = 50;
    constexpr int DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
    constexpr int FILA_TITULOS_PANELES = 100;
    constexpr int FILA_BOTONES_EJECUTIVOS = 600;
    constexpr int FILA_BOTONES_GENERALES = 800;
    constexpr int MARGEN_IZQ_PANELES = 50;
    constexpr int DESPLAZAMIENTO_LATERAL = ANCHO_PANEL + 42;
} // namespace medidas

namespace colores {
    const auto COLOR_FONDO = sf::Color(60, 0, 150);
    const auto COLOR_TEXTO_INSTRUCCIONES = sf::Color::Yellow;
    const auto COLOR_TEXTO_RESULTADO = sf::Color(255, 160, 0);
} // namespace colores

int obtener_posicion_x_panel(IndicePanel indice_panel);
