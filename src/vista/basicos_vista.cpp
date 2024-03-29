#include "basicos_vista.h"

namespace medidas {
    constexpr float DESPLAZAMIENTO_LATERAL = ANCHO_PANEL + (float)42;
} // namespace medidas

IndicePanel paneles_posibles[] = {
    IndicePanel::PANEL_ENCARGAR,       //
    IndicePanel::PANEL_EN_PREPARACION, //
    IndicePanel::PANEL_PREPARADAS,     //
    IndicePanel::PANEL_PEDIDOS,        //
};

namespace {
    float _obtener_posicion_x_panel(IndicePanel indice_panel) {
        return medidas::MARGEN_IZQ_PANELES + (medidas::DESPLAZAMIENTO_LATERAL *
                                              static_cast<float>(indice_panel));
    }
} // namespace

sf::Vector2f basicos_vista::obtener_posicion_panel( //
    const IndicePanel &indice_panel
) {
    const auto pos_x_panel = _obtener_posicion_x_panel(indice_panel);
    const auto pos_y_panel = medidas::MARGEN_TOP_PANELES;
    return {pos_x_panel, pos_y_panel};
}

sf::FloatRect basicos_vista::obtener_rect_panel( //
    const IndicePanel &indice_panel
) {
    const auto posicion = obtener_posicion_panel(indice_panel);
    return sf::FloatRect(posicion, {medidas::ANCHO_PANEL, medidas::ALTO_PANEL});
}
