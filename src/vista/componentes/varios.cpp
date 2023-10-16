#include "varios.h"

sf::Text crearEtiqueta(
    int tamano, const sf::Font &font, const sf::Color &color,
    const sf::Vector2f &posicion
) {
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta("<Placeholder>", font, tamano);
    etiqueta.setFillColor(color);
    etiqueta.setPosition(posicion);
    return etiqueta;
}

/* Sobrecarga para usar EstiloTexto */
sf::Text
crearEtiqueta(const EstiloTexto &estilo_texto, const sf::Vector2f &posicion) {
    return crearEtiqueta(
        estilo_texto.tamano, estilo_texto.font, estilo_texto.color, posicion
    );
}
