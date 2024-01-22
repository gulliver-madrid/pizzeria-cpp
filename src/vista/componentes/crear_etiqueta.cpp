#include "crear_etiqueta.h"
#include "etiqueta.h"
#include <SFML/Graphics/Text.hpp>
#include <iostream>

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const std::string nombre  //
) {
    return std::make_shared<Etiqueta>(texto, tamano_fuente, nombre);
}

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,     //
    int tamano_fuente,            //
    const sf::Color &color,       //
    const sf::Vector2f &posicion, //
    const std::string nombre      //

) {
    return std::make_shared<Etiqueta>(
        texto, tamano_fuente, color, posicion, nombre
    );
}

/* Sobrecarga para usar EstiloTexto */
std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,     //
    const EstiloTexto &estilo,    //
    const sf::Vector2f &posicion, //
    const std::string nombre      //
) {
    return std::make_shared<Etiqueta>(texto, estilo, posicion, nombre);
}
