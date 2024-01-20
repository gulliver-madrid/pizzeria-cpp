#pragma once

#include "../componente.h"
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
    Etiqueta(
        const std::string &texto, //
        int tamano_fuente,        //
        const OptionalFont &font  //
    );
    Etiqueta(
        const std::string &texto,    //
        int tamano_fuente,           //
        const sf::Color &color,      //
        const OptionalFont &font,    //
        const sf::Vector2f &posicion //

    );
    /* Sobrecarga para usar EstiloTexto */
    Etiqueta(
        const std::string &texto,    //
        const EstiloTexto &estilo,   //
        const OptionalFont &font,    //
        const sf::Vector2f &posicion //
    );

    void actualizar_texto(const std::string &texto);
    sf::FloatRect get_global_bounds();
    void set_position(float x, float y);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
