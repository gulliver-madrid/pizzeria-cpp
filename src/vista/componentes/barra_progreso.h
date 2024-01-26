#pragma once

#include "../../shared/font.h"
#include "../componente.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <string>

class Etiqueta;

struct ColorPair {
    sf::Color bg;
    sf::Color fg;
};

///////////////////////////////////////////
// BarraProgreso
//////////////////////////////////////////

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
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// BarraProgresoConNombre
///////////////////////////////////////////

// Colores de una BarraProgresoConNombre
struct BPNColors {
    ColorPair color_pair;
    sf::Color color_texto;
};

class BarraProgresoConNombre : public ComponenteConFont {
  private:
    std::shared_ptr<Etiqueta> etiqueta;
    BarraProgreso bp;
    static std::shared_ptr<Etiqueta> _crear_etiqueta(
        const std::string &texto,           //
        const sf::Vector2f &posicion_barra, //
        const sf::Color &color_texto        //
    );

  public:
    BarraProgresoConNombre(
        const sf::Vector2f &dimensiones, //
        const std::string &texto,        //
        const sf::Vector2f &posicion,    //
        const BPNColors &bpn_colors      //
    );
    void actualizar_porcentaje(int porcentaje);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
