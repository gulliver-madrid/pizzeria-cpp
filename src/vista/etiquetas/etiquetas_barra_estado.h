#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/Drawable.hpp>

namespace sf {
    class Font;
    class RenderTarget;
    class Text;
    class Time;
} // namespace sf

class EtiquetasBarraEstado : public ObjetoConFont, public sf::Drawable {

  private:
    std::unique_ptr<sf::Text> etiqueta;

  public:
    EtiquetasBarraEstado(const OptionalFont &);
    void actualizar(const sf::Time &, const sf::Time &);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
