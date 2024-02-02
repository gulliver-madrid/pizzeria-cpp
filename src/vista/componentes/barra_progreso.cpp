#include "barra_progreso.h"
#include "../../templates/dibujar_elementos.h"
#include "crear_etiqueta.h"
#include "etiqueta.h"
#include <cassert>

///////////////////////////////////////////
// BarraProgreso
///////////////////////////////////////////

// Metodos estaticos para crear los miembros de BarraProgreso
sf::RectangleShape BarraProgreso::_create_filled_rect(
    const sf::Vector2f &dimensiones, //
    const sf::Vector2f &posicion,    //
    const sf::Color color            //
) {
    sf::RectangleShape shape;
    shape.setSize(dimensiones);
    shape.setFillColor(color);
    shape.setPosition(posicion);
    return shape;
}

BarraProgreso::BarraProgreso(
    const sf::Vector2f &dimensiones, //
    const sf::Vector2f &posicion,    //
    const ColorPair &color_pair      //
)
    : dimensiones(dimensiones),                                         //
      fondo(_create_filled_rect(dimensiones, posicion, color_pair.bg)), //
      relleno(_create_filled_rect(dimensiones, posicion, color_pair.fg) //
      ) {}

/* Actualiza el porcentaje de la barra de progreso */
void BarraProgreso::actualizar_porcentaje(int porcentaje) {
    relleno.setSize(
        sf::Vector2f(dimensiones.x * porcentaje / 100, dimensiones.y)
    );
}
void BarraProgreso::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    dibujar_elementos(target, std::make_tuple(fondo, relleno));
}

///////////////////////////////////////////
// BarraProgresoConNombre
///////////////////////////////////////////

std::shared_ptr<Etiqueta> BarraProgresoConNombre::_crear_etiqueta(
    const std::string &texto,           //
    const sf::Vector2f &posicion_barra, //
    const sf::Color &color_texto        //
) {
    return crear_etiqueta(
        texto,                                         //
        24,                                            //
        color_texto,                                   //
        {posicion_barra.x + 20, posicion_barra.y + 5}, //
        std::string("etiqueta barra progreso")
    );
}

BarraProgresoConNombre::BarraProgresoConNombre(
    const sf::Vector2f &dimensiones, //
    const std::string &texto,        //
    const sf::Vector2f &posicion,    //
    const ColoresBPN &colores_bpn      //
)
    : bp(dimensiones, posicion, colores_bpn.color_pair),
      etiqueta(_crear_etiqueta(texto, posicion, colores_bpn.color_texto)) {
    add_child(etiqueta);
}

void BarraProgresoConNombre::actualizar_porcentaje(int porcentaje) { //
    bp.actualizar_porcentaje(porcentaje);
}
void BarraProgresoConNombre::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {                     //
    target.draw(bp);
    target.draw(*etiqueta);
}
