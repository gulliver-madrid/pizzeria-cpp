#pragma once

#include <SFML/Graphics.hpp>

///////////////////////////////////////////
// BarraProgreso
//////////////////////////////////////////

struct BarraProgreso {
  private:
    sf::Vector2f dimensiones;
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
    static sf::RectangleShape crear_fondo( //
        const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
    );
    static sf::RectangleShape crear_relleno(
        const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
    );

  public:
    BarraProgreso(
        const sf::Vector2f &dimensiones, const sf::Vector2f &posicion
    );
    void actualizar_porcentaje(int porcentaje);
    void dibujar(sf::RenderWindow &ventana) const;
};

///////////////////////////////////////////
// BarraProgresoConNombre
///////////////////////////////////////////

struct BarraProgresoConNombre {
  private:
    sf::Text etiqueta;
    BarraProgreso bp;
    static sf::Text crear_etiqueta(
        const std::string &texto,     //
        const sf::Vector2f &posicion, //
        const sf::Font &font          //
    );

  public:
    BarraProgresoConNombre(
        const sf::Vector2f &dimensiones, //
        const std::string &texto,        //
        const sf::Vector2f &posicion,    //
        const sf::Font &font             //
    );
    void actualizar_porcentaje(int porcentaje);
    void dibujar(sf::RenderWindow &ventana) const;
};
