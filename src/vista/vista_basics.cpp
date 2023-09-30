#include "vista_basics.h"

namespace medidas {
    constexpr int MARGEN_IZQ_PANELES = 50;
    constexpr int MARGEN_TOP_PANELES = 50;
} // namespace medidas

int obtener_posicion_x_panel(IndicePanel indice_panel) {
    return medidas::MARGEN_IZQ_PANELES +
           (medidas::DESPLAZAMIENTO_LATERAL * static_cast<int>(indice_panel));
}

sf::Vector2i obtener_posicion_panel(IndicePanel indice_panel) {
    int pos_x_panel = obtener_posicion_x_panel(indice_panel);
    int pos_y_panel = medidas::MARGEN_TOP_PANELES;
    return {pos_x_panel, pos_y_panel};
}
