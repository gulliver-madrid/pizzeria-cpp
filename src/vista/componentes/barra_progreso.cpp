#include "barra_progreso.h"
#include <cassert>

namespace colores {
    const sf::Color COLOR_BARRA_PROGRESO_FONDO = {230, 230, 230};
    const sf::Color COLOR_BARRA_PROGRESO_RELLENO = {
        255, 140, 0}; // 30, 144, 255
    const sf::Color COLOR_BARRA_PROGRESO_TEXTO = {0, 0, 0};
} // namespace colores

void BarraProgreso::setup(
    const sf::Vector2f &dimensiones_, const sf::Vector2f &posicion
) {
    assert(dimensiones == sf::Vector2f(0, 0));
    dimensiones = dimensiones_;
    fondo = sf::RectangleShape(dimensiones);
    relleno = sf::RectangleShape(sf::Vector2f(0, 0));
    fondo.setFillColor(sf::Color(colores::COLOR_BARRA_PROGRESO_FONDO));
    relleno.setFillColor(sf::Color(colores::COLOR_BARRA_PROGRESO_RELLENO));
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
    const sf::Vector2f &dimensiones, //
    const std::string &texto,        //
    const sf::Vector2f &posicion,    //
    const sf::Font &font             //
) {
    bp.setup(dimensiones, posicion);
    etiqueta = sf::Text(texto, font, 24);
    etiqueta.setFillColor(sf::Color(colores::COLOR_BARRA_PROGRESO_TEXTO));
    etiqueta.setPosition(posicion.x + 20, posicion.y + 5);
}

void BarraProgresoConNombre::update(int porcentaje) { //
    bp.update(porcentaje);
}
void BarraProgresoConNombre::dibujar(sf::RenderWindow &ventana) const { //
    ventana.draw(bp.fondo);
    ventana.draw(bp.relleno);
    ventana.draw(etiqueta);
}
