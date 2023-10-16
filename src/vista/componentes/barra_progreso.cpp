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

///////////////////////////////////////////
// BarraProgreso
///////////////////////////////////////////

// Metodos estaticos para crear los miembros de BarraProgreso
sf::RectangleShape BarraProgreso::crear_fondo(
    const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
) {
    sf::RectangleShape fondo;
    fondo.setSize(dimensiones);
    fondo.setFillColor(colores::barra_progreso::FONDO);
    fondo.setPosition(posicion);
    return fondo;
}
sf::RectangleShape BarraProgreso::crear_relleno(
    const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
) {
    sf::RectangleShape relleno;
    relleno.setFillColor(colores::barra_progreso::RELLENO);
    relleno.setPosition(posicion);
    return relleno;
}

BarraProgreso::BarraProgreso(
    const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
)
    : dimensiones(dimensiones),                    //
      fondo(crear_fondo(dimensiones, posicion)),   //
      relleno(crear_relleno(dimensiones, posicion) //
      ) {}

/* Actualiza el porcentaje de la barra de progreso */
void BarraProgreso::actualizar_porcentaje(int porcentaje) {
    relleno.setSize(
        sf::Vector2f(dimensiones.x * porcentaje / 100, dimensiones.y)
    );
}
void BarraProgreso::dibujar(sf::RenderWindow &ventana) const {
    ventana.draw(fondo);
    ventana.draw(relleno);
}

///////////////////////////////////////////
// BarraProgresoConNombre
///////////////////////////////////////////

sf::Text BarraProgresoConNombre::crear_etiqueta(
    const std::string &texto,     //
    const sf::Vector2f &posicion, //
    const sf::Font &font          //
) {
    auto etiqueta = sf::Text(texto, font, 24);
    etiqueta.setFillColor(colores::barra_progreso::TEXTO);
    etiqueta.setPosition(posicion.x + 20, posicion.y + 5);
    return etiqueta;
}

BarraProgresoConNombre::BarraProgresoConNombre(
    const sf::Vector2f &dimensiones, //
    const std::string &texto,        //
    const sf::Vector2f &posicion,    //
    const sf::Font &font             //
)
    : bp(dimensiones, posicion),
      etiqueta(crear_etiqueta(texto, posicion, font)) {}

void BarraProgresoConNombre::actualizar_porcentaje(int porcentaje) { //
    bp.actualizar_porcentaje(porcentaje);
}
void BarraProgresoConNombre::dibujar(sf::RenderWindow &ventana) const { //
    bp.dibujar(ventana);
    ventana.draw(etiqueta);
}
