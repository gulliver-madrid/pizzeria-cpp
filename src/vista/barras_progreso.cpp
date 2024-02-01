#include "barras_progreso.h"
#include "basicos_vista.h"
#include "vista_data.h"

namespace medidas {
    constexpr float DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
} // namespace medidas

/* Crea y actualiza las barras de progreso */
std::vector<std::shared_ptr<BarraProgresoConNombre>> crear_barras_progreso(
    const PresentacionPreparacionPizzas &presentacion,
    const sf::Vector2f &pos_panel
) {
    constexpr float ancho = 300;
    constexpr float largo = 40;
    static const auto dimensiones = sf::Vector2f(ancho, largo);
    static const BPNColors bpn_colors = {
        colores::barra_progreso::FONDO,
        colores::barra_progreso::RELLENO,
        colores::barra_progreso::TEXTO,
    };
    constexpr float diferencia_vertical =
        medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;

    const auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    const auto pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;

    std::vector<std::shared_ptr<BarraProgresoConNombre>> barras{};
    size_t i = 0;
    for (auto &presentacion_pizza : presentacion) {
        const auto offset_y = i * diferencia_vertical;
        const auto pos_y = pos_y_inicial + offset_y;
        const auto posicion = sf::Vector2f(pos_x, pos_y);
        auto bpn = std::make_shared<BarraProgresoConNombre>(
            dimensiones,                     //
            presentacion_pizza.nombre_pizza, //
            posicion,                        //
            bpn_colors                       //
        );
        bpn->actualizar_porcentaje(presentacion_pizza.porcentaje);
        barras.push_back(bpn);
        i++;
    }

    return barras;
}
