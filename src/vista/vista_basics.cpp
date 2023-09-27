#include "vista_basics.h"

int obtener_posicion_x_panel(IndicePanel indice_panel) {
    return medidas::MARGEN_IZQ_PANELES +
           (medidas::DESPLAZAMIENTO_LATERAL * static_cast<int>(indice_panel));
}
