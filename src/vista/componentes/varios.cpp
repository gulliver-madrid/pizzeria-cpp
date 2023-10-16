#include "varios.h"

sf::Text crearEtiqueta(
    int tamano, const sf::Color &color, const sf::Font &font,
    const sf::Vector2f &posicion
) {
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta("<Placeholder>", font, tamano);
    etiqueta.setFillColor(color);
    etiqueta.setPosition(posicion);
    return etiqueta;
}

/* Sobrecarga para usar EstiloTexto */
sf::Text crearEtiqueta(
    const EstiloTexto &estilo, const sf::Font &font,
    const sf::Vector2f &posicion
) {
    return crearEtiqueta(estilo.tamano, estilo.color, font, posicion);
}
