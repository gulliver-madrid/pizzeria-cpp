#include "barras_progreso.h"
#include "basicos_vista.h"
#include "vista_data.h"

namespace medidas {
    constexpr float DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
} // namespace medidas

/* Crea y actualiza las barras de progreso */
std::vector<std::shared_ptr<BarraProgresoConNombre>> crear_barras_progreso(
    const VistaPreparacionPizzas &vista_preparacion_pizzas,
    const sf::Vector2f &pos_panel
) {
    std::vector<std::shared_ptr<BarraProgresoConNombre>> vect{};
    const auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    const auto pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
    const float ancho = 300;
    const float largo = 40;
    const auto dimensiones = sf::Vector2f(ancho, largo);
    size_t i = 0;
    for (auto &vista_preparacion_pizza : vista_preparacion_pizzas) {
        const auto offset_y =
            i * medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;
        const auto pos_y = pos_y_inicial + offset_y;
        const auto posicion = sf::Vector2f(pos_x, pos_y);
        const BPNColors bpn_colors = {
            colores::barra_progreso::FONDO,
            colores::barra_progreso::RELLENO,
            colores::barra_progreso::TEXTO,
        };
        auto bpn = std::make_shared<BarraProgresoConNombre>(
            dimensiones,                          //
            vista_preparacion_pizza.nombre_pizza, //
            posicion,                             //
            bpn_colors                            //
        );
        bpn->actualizar_porcentaje(vista_preparacion_pizza.porcentaje);
        vect.push_back(bpn);
        i++;
    }

    return vect;
}
