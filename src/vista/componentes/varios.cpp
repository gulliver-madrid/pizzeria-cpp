#include "varios.h"
#include "etiqueta.h"
#include <SFML/Graphics/Text.hpp>
#include <iostream>

sf::Text crearEtiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const OptionalFont &font  //
) {
    sf::Text etiqueta;
    etiqueta.setString(texto);
    if (font.exists()) {
        etiqueta.setFont(*font.get_pointer());
        etiqueta.setCharacterSize(tamano_fuente);
    }
    return etiqueta;
}

Etiqueta crear_etiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const OptionalFont &font  //
) {
    return Etiqueta(texto, tamano_fuente, font);
}

sf::Text crearEtiqueta(
    const std::string &texto,    //
    int tamano_fuente,           //
    const sf::Color &color,      //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //

) {
    sf::Text etiqueta = crearEtiqueta(texto, tamano_fuente, font);
    etiqueta.setFillColor(color);
    etiqueta.setPosition(posicion);
    return etiqueta;
}

/* Sobrecarga para usar EstiloTexto */
sf::Text crearEtiqueta(
    const std::string &texto,    //
    const EstiloTexto &estilo,   //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //
) {
    return crearEtiqueta(texto, estilo.tamano, estilo.color, font, posicion);
}

std::unique_ptr<sf::Text> crear_puntero_a_etiqueta(
    const std::string &texto,    //
    const EstiloTexto &estilo,   //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //
) {
    auto etiqueta = std::make_unique<sf::Text>();
    etiqueta->setString(texto);
    if (font.exists()) {
        etiqueta->setFont(*font.get_pointer());
        etiqueta->setCharacterSize(estilo.tamano);
    }
    etiqueta->setFillColor(estilo.color);
    etiqueta->setPosition(posicion);
    return etiqueta;
}
