#include "barras_progreso.h"
#include "../modelo/modelo.h"
#include "vista_basics.h"

#define COLOR_BARRA_PROGRESO_FONDO 230, 230, 230
#define COLOR_BARRA_PROGRESO_RELLENO 255, 140, 0 // 30, 144, 255
#define COLOR_BARRA_PROGRESO_TEXTO 0, 0, 0

namespace medidas {
    constexpr int DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
} // namespace medidas

void BarraProgreso::setup(
    const sf::Vector2f &dimensiones, int porcentaje,
    const sf::Vector2f &posicion
) {
    fondo = sf::RectangleShape(dimensiones);
    relleno = sf::RectangleShape(
        sf::Vector2f(dimensiones.x * porcentaje / 100, dimensiones.y)
    );
    fondo.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_FONDO));
    relleno.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_RELLENO));
    fondo.setPosition(posicion);
    relleno.setPosition(posicion);
}

std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, const sf::Font &font
) {
    std::vector<BarraProgresoConNombre> vect{};
    auto pos_panel = obtener_posicion_panel(IndicePanel::PANEL_EN_PREPARACION);
    int pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
    int ancho = 300;
    int largo = 40;
    auto dimensiones = sf::Vector2f(ancho, largo);
    int i = 0;
    for (auto &porcentaje : preparacion.datos) {
        BarraProgresoConNombre bpn;
        BarraProgreso &bp = bpn.bp;
        int offset_y = i * medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;
        int pos_y = pos_y_inicial + offset_y;
        auto posicion = sf::Vector2f(pos_x, pos_y);
        bp.setup(dimensiones, porcentaje.porcentaje, posicion);
        bpn.etiqueta =
            sf::Text(tipo_pizza_to_string[porcentaje.tipo], font, 24);
        bpn.etiqueta.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_TEXTO));
        bpn.etiqueta.setPosition(pos_x + 20, pos_y + 5);
        vect.push_back(bpn);
        i++;
    }
    return vect;
}
