#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

enum class IndicePanel {
    // Contiene los botones para encargar las pizzas
    PANEL_ENCARGAR,
    // Informa del grado de progreso de la preparacion de las pizzas
    PANEL_EN_PREPARACION,
    // Muestra el estado del area de preparadas
    PANEL_PREPARADAS,
    // Muestra el estado de los pedidos
    PANEL_PEDIDOS,
};

constexpr size_t NUMERO_DE_TIPOS_DE_PANEL = 4;
extern IndicePanel paneles_posibles[NUMERO_DE_TIPOS_DE_PANEL];

namespace medidas {
    constexpr float ANCHO_PANEL = 390;
    constexpr float ALTO_PANEL = 700;

    // Margenes externos de los paneles
    constexpr float MARGEN_IZQ_PANELES = 50;
    constexpr float MARGEN_TOP_PANELES = 50;

    constexpr float MARGEN_IZQ_ETIQUETAS = 30;
    constexpr float FILA_BOTONES_GENERALES = 800;
    constexpr float FILA_BARRA_ESTADO = FILA_BOTONES_GENERALES;
    constexpr float SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES = 25;

    // Posiciones desde el inicio del panel respectivo
    constexpr float FILA_TITULOS_PANELES = 50;
    constexpr float FILA_CONTENIDO_PANEL = 150;
} // namespace medidas

namespace colores {
    const auto COLOR_FONDO = sf::Color(60, 0, 150);
    const auto TEXTO_INSTRUCCIONES = sf::Color::Yellow;
    const auto TEXTO_RESULTADO = sf::Color(255, 160, 0);
} // namespace colores

namespace basicos_vista {
    sf::Vector2f obtener_posicion_panel(const IndicePanel &);
    sf::FloatRect obtener_rect_panel(const IndicePanel &);
} // namespace basicos_vista
