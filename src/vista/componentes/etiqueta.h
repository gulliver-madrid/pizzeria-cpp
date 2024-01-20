#pragma once

#include "../../shared/font.h"
#include "../componente.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

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
    ) {
        this->font = font;
        etiqueta.setString(texto);
        if (font.exists()) {
            etiqueta.setFont(*font.get_pointer());
            etiqueta.setCharacterSize(tamano_fuente);
        };
    }
    Etiqueta(
        const std::string &texto,    //
        int tamano_fuente,           //
        const sf::Color &color,      //
        const OptionalFont &font,    //
        const sf::Vector2f &posicion //

    )
        : Etiqueta(texto, tamano_fuente, font) {
        etiqueta.setFillColor(color);
        etiqueta.setPosition(posicion);
    }

    /* Sobrecarga para usar EstiloTexto */
    Etiqueta(
        const std::string &texto,    //
        const EstiloTexto &estilo,   //
        const OptionalFont &font,    //
        const sf::Vector2f &posicion //
    )
        : Etiqueta(texto, estilo.tamano, estilo.color, font, posicion) {}

    void actualizar_texto(const std::string &texto) { //
        etiqueta.setString(texto);
    }
    sf::FloatRect get_global_bounds() { //
        return etiqueta.getGlobalBounds();
    }
    void set_position(float x, float y) { //
        etiqueta.setPosition(x, y);
    }
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override {
        assert(font.exists());
        target.draw(etiqueta);
    };
};
