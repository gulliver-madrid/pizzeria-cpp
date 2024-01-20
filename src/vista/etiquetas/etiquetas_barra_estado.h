#pragma once

#include "../../shared/font.h"
#include <SFML/Graphics/Drawable.hpp>

namespace sf {
    class Font;
    class RenderTarget;
    class Time;
} // namespace sf

class Etiqueta;

class EtiquetasBarraEstado : public ObjetoConFont, public sf::Drawable {

  private:
    std::shared_ptr<Etiqueta> etiqueta;

  public:
    EtiquetasBarraEstado(const OptionalFont &);
    void actualizar(const sf::Time &, const sf::Time &);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
