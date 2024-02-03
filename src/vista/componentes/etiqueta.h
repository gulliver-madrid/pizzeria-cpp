#pragma once

#include "componente.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

class OptionalFont;
struct EstiloTexto {
    const int tamano;
    const sf::Color &color;
};

class Etiqueta : public ComponenteConFont {
  private:
    sf::Text etiqueta;

  public:
    // nombre a propositos de debug
    std::string nombre;
    Etiqueta(
        const std::string &texto, //
        int tamano_fuente,        //
        const std::string nombre  //
    );
    Etiqueta(
        const std::string &texto,     //
        int tamano_fuente,            //
        const sf::Color &color,       //
        const sf::Vector2f &posicion, //
        const std::string nombre      //
    );

    /* Sobrecarga para usar EstiloTexto */
    Etiqueta(
        const std::string &texto,     //
        const EstiloTexto &estilo,    //
        const sf::Vector2f &posicion, //
        const std::string nombre      //
    );

    void actualizar_texto(const std::string &texto);
    sf::FloatRect get_global_bounds();
    void set_position(float x, float y);
    virtual void set_font(const OptionalFont &new_font) override;
    void set_color(const sf::Color &);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
