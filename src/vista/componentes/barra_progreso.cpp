#include "barra_progreso.h"
#include <cassert>

namespace colores {
    namespace barra_progreso {
        using sf::Color;
        const Color FONDO = {230, 230, 230};
        const Color RELLENO = {255, 140, 0}; // 30, 144, 255
        const Color TEXTO = {0, 0, 0};
    } // namespace barra_progreso
} // namespace colores

BarraProgreso::BarraProgreso(
    const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
)
    : dimensiones(dimensiones) {
    assert(fondo.getSize() == Vector2f_CERO);
    assert(relleno.getSize() == Vector2f_CERO);
    fondo.setSize(dimensiones);
    fondo.setFillColor(colores::barra_progreso::FONDO);
    relleno.setFillColor(colores::barra_progreso::RELLENO);
    fondo.setPosition(posicion);
    relleno.setPosition(posicion);
}

/* Actualiza el porcentaje de la barra de progreso */
void BarraProgreso::update(int porcentaje) {
    relleno.setSize(
        sf::Vector2f(dimensiones.x * porcentaje / 100, dimensiones.y)
    );
}
void BarraProgreso::dibujar(sf::RenderWindow &ventana) const {
    ventana.draw(fondo);
    ventana.draw(relleno);
}

BarraProgresoConNombre::BarraProgresoConNombre(
    const sf::Vector2f &dimensiones, //
    const std::string &texto,        //
    const sf::Vector2f &posicion,    //
    const sf::Font &font             //
)
    : bp(dimensiones, posicion) {
    etiqueta = sf::Text(texto, font, 24);
    etiqueta.setFillColor(colores::barra_progreso::TEXTO);
    etiqueta.setPosition(posicion.x + 20, posicion.y + 5);
}

void BarraProgresoConNombre::update(int porcentaje) { //
    bp.update(porcentaje);
}
void BarraProgresoConNombre::dibujar(sf::RenderWindow &ventana) const { //
    bp.dibujar(ventana);
    ventana.draw(etiqueta);
}
