#include "barras_progreso.h"
#include "../modelo/modelo.h"
#include "vista_basics.h"

namespace medidas {
    constexpr int DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
} // namespace medidas

/* Crea y actualiza las barras de progreso */
std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, const sf::Vector2f &pos_panel,
    const sf::Font &font
) {
    std::vector<BarraProgresoConNombre> vect{};
    const int pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    const int pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
    const int ancho = 300;
    const int largo = 40;
    const auto dimensiones = sf::Vector2f(ancho, largo);
    int i = 0;
    for (auto &preparacion_pizza : preparacion.datos) {
        const int offset_y =
            i * medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;
        const int pos_y = pos_y_inicial + offset_y;
        const auto posicion = sf::Vector2f(pos_x, pos_y);
        const auto str = tipo_pizza_to_string[preparacion_pizza.tipo];
        BarraProgresoConNombre bpn(dimensiones, str, posicion, font);
        bpn.actualizar_porcentaje(preparacion_pizza.porcentaje);
        vect.push_back(bpn);
        i++;
    }

    return vect;
}
