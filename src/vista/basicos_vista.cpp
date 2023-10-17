#include "basicos_vista.h"

namespace medidas {
    constexpr int MARGEN_IZQ_PANELES = 50;
    constexpr int MARGEN_TOP_PANELES = 50;
    constexpr int DESPLAZAMIENTO_LATERAL = ANCHO_PANEL + 42;
} // namespace medidas

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
    const float pos_y_panel = medidas::MARGEN_TOP_PANELES;
    return {pos_x_panel, pos_y_panel};
}
