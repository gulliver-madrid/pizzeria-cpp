#include "varios.h"

sf::Text crearEtiqueta(
    const std::string &texto,    //
    int tamano_fuente,           //
    const sf::Color &color,      //
    const sf::Font &font,        //
    const sf::Vector2f &posicion //

) {
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta(texto, font, tamano_fuente);
    etiqueta.setFillColor(color);
    etiqueta.setPosition(posicion);
    return etiqueta;
}

/* Sobrecarga para usar EstiloTexto */
sf::Text crearEtiqueta(
    const std::string &texto,    //
    const EstiloTexto &estilo,   //
    const sf::Font &font,        //
    const sf::Vector2f &posicion //

) {
    return crearEtiqueta(texto, estilo.tamano, estilo.color, font, posicion);
}
