#include "barras_progreso.h"
#include "../modelo/modelo.h"
#include "vista_basics.h"
#include <cassert>

#define COLOR_BARRA_PROGRESO_FONDO 230, 230, 230
#define COLOR_BARRA_PROGRESO_RELLENO 255, 140, 0 // 30, 144, 255
#define COLOR_BARRA_PROGRESO_TEXTO 0, 0, 0

namespace medidas {
    constexpr int DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
} // namespace medidas

void BarraProgreso::setup(
    const sf::Vector2f &dimensiones_, const sf::Vector2f &posicion
) {
    assert(dimensiones == sf::Vector2f(0, 0));
    dimensiones = dimensiones_;
    fondo = sf::RectangleShape(dimensiones);
    relleno = sf::RectangleShape(sf::Vector2f(0, 0));
    fondo.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_FONDO));
    relleno.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_RELLENO));
    fondo.setPosition(posicion);
    relleno.setPosition(posicion);
}

/* Actualiza el porcentaje de la barra de progreso */
void BarraProgreso::update(int porcentaje) {
    relleno.setSize(
        sf::Vector2f(dimensiones.x * porcentaje / 100, dimensiones.y)
    );
}

void BarraProgresoConNombre::setup(
    sf::Vector2f &dimensiones,    //
    const TipoPizza tp,           //
    const sf::Vector2f &posicion, //
    const sf::Font &font          //
) {
    bp.setup(dimensiones, posicion);
    etiqueta = sf::Text(tipo_pizza_to_string[tp], font, 24);
    etiqueta.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_TEXTO));
    etiqueta.setPosition(posicion.x + 20, posicion.y + 5);
}

void BarraProgresoConNombre::update(int porcentaje) { //
    bp.update(porcentaje);
}
void BarraProgresoConNombre::dibujar(sf::RenderWindow &ventana) { //
    ventana.draw(bp.fondo);
    ventana.draw(bp.relleno);
    ventana.draw(etiqueta);
}

/* Crea y actualiza las barras de progreso */
std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, sf::Vector2i &pos_panel,
    const sf::Font &font
) {
    std::vector<BarraProgresoConNombre> vect{};
    int pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
    int ancho = 300;
    int largo = 40;
    auto dimensiones = sf::Vector2f(ancho, largo);
    int i = 0;
    for (auto &preparacion_pizza : preparacion.datos) {
        BarraProgresoConNombre bpn;
        int offset_y = i * medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;
        int pos_y = pos_y_inicial + offset_y;
        auto posicion = sf::Vector2f(pos_x, pos_y);
        bpn.setup(dimensiones, preparacion_pizza.tipo, posicion, font);
        bpn.update(preparacion_pizza.porcentaje);
        vect.push_back(bpn);
        i++;
    }

    return vect;
}
