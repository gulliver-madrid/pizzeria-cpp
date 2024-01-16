#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <optional>

///////////////////////////////////////////
// BarraProgreso
//////////////////////////////////////////

struct ColorPair {
    sf::Color bg;
    sf::Color fg;
};

struct BarraProgreso : public sf::Drawable {
  private:
    sf::Vector2f dimensiones;
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
    static sf::RectangleShape _create_filled_rect( //
        const sf::Vector2f &dimensiones,           //
        const sf::Vector2f &posicion,              //
        const sf::Color color                      //
    );

  public:
    BarraProgreso(
        const sf::Vector2f &dimensiones, //
        const sf::Vector2f &posicion,    //
        const ColorPair &color_pair      //
    );
    void actualizar_porcentaje(int porcentaje);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

///////////////////////////////////////////
// BarraProgresoConNombre
///////////////////////////////////////////

// Colores de una BarraProgresoConNombre
struct BPNColors {
    ColorPair color_pair;
    sf::Color color_texto;
};

struct BarraProgresoConNombre : public sf::Drawable {
  private:
    sf::Text etiqueta;
    BarraProgreso bp;
    static sf::Text _crear_etiqueta(
        const std::string &texto,           //
        const sf::Vector2f &posicion_barra, //
        const sf::Color &color_texto,       //
        const OptionalFont &                //
    );

  public:
    BarraProgresoConNombre(
        const sf::Vector2f &dimensiones, //
        const std::string &texto,        //
        const sf::Vector2f &posicion,    //
        const BPNColors &bpn_colors,     //
        const OptionalFont &             //
    );
    void actualizar_porcentaje(int porcentaje);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
