#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <optional>
#include <string>

class Etiqueta;
struct EstiloTexto;

namespace sf {
    class Font;
    class Text;
} // namespace sf

namespace medidas {
    constexpr int TAMANO_TEXTO_GRANDE = 32;
} // namespace medidas

const auto Vector2f_CERO = sf::Vector2f(0, 0);

///// Creadores de Etiqueta /////

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const std::string nombre  //
);

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,     //
    int tamano_fuente,            //
    const sf::Color &color,       //
    const sf::Vector2f &posicion, //
    const std::string nombre      //

);
// const sf::Vector2f &posicion = Vector2f_CERO //

/* Sobrecarga para usar EstiloTexto */
std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,     //
    const EstiloTexto &estilo,    //
    const sf::Vector2f &posicion, //
    const std::string nombre      //
);
