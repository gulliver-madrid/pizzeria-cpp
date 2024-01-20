#include "crear_etiqueta.h"
#include "etiqueta.h"
#include <SFML/Graphics/Text.hpp>
#include <iostream>

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const OptionalFont &font  //
) {
    return std::make_shared<Etiqueta>(texto, tamano_fuente, font);
}

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,    //
    int tamano_fuente,           //
    const sf::Color &color,      //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //

) {
    return std::make_shared<Etiqueta>(
        texto, tamano_fuente, color, font, posicion
    );
}

/* Sobrecarga para usar EstiloTexto */
std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,    //
    const EstiloTexto &estilo,   //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //
) {
    return std::make_shared<Etiqueta>(texto, estilo, font, posicion);
}
