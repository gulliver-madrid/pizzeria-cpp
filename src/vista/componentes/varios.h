
#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <optional>
#include <string>

namespace sf {
    class Font;
    class Text;
} // namespace sf

class Etiqueta;

namespace medidas {
    constexpr int TAMANO_TEXTO_GRANDE = 32;
} // namespace medidas

struct EstiloTexto;

const auto Vector2f_CERO = sf::Vector2f(0, 0);

///// Creadores de Etiqueta /////

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const OptionalFont &      //
);

std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,    //
    int tamano_fuente,           //
    const sf::Color &color,      //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //

);

/* Sobrecarga para usar EstiloTexto */
std::shared_ptr<Etiqueta> crear_etiqueta(
    const std::string &texto,    //
    const EstiloTexto &estilo,   //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //
);

///// Creadores de sf::Text /////

sf::Text crearEtiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const OptionalFont &      //
);

sf::Text crearEtiqueta(
    const std::string &texto,                    //
    int tamano_fuente,                           //
    const sf::Color &,                           //
    const OptionalFont &,                        //
    const sf::Vector2f &posicion = Vector2f_CERO //

);
sf::Text crearEtiqueta(
    const std::string &texto,                    //
    const EstiloTexto &,                         //
    const OptionalFont &,                        //
    const sf::Vector2f &posicion = Vector2f_CERO //
);
