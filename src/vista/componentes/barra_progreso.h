#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

///////////////////////////////////////////
// BarraProgreso
//////////////////////////////////////////

struct ColorPair {
    sf::Color bg;
    sf::Color fg;
};

struct BarraProgreso {
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
    void dibujar(sf::RenderTarget &target) const;
};

///////////////////////////////////////////
// BarraProgresoConNombre
///////////////////////////////////////////

// Colores de una BarraProgresoConNombre
struct BPNColors {
    ColorPair color_pair;
    sf::Color color_texto;
};

struct BarraProgresoConNombre {
  private:
    sf::Text etiqueta;
    BarraProgreso bp;
    static sf::Text _crear_etiqueta(
        const std::string &texto,           //
        const sf::Vector2f &posicion_barra, //
        const sf::Color &color_texto,       //
        const sf::Font &                    //
    );

  public:
    BarraProgresoConNombre(
        const sf::Vector2f &dimensiones, //
        const std::string &texto,        //
        const sf::Vector2f &posicion,    //
        const BPNColors &bpn_colors,     //
        const sf::Font &                 //
    );
    void actualizar_porcentaje(int porcentaje);
    void dibujar(sf::RenderTarget &target) const;
};
