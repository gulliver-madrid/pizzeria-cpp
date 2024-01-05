#pragma once

#include "../../shared.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

namespace sf {
    class Font;
    class RenderTarget;
} // namespace sf

struct EtiquetasBarraEstado : public ObjetoConFont, public sf::Drawable {

  private:
    sf::Text etiqueta;

  public:
    EtiquetasBarraEstado(const sf::Font &);
    void actualizar(const sf::Time &, const sf::Time &);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
