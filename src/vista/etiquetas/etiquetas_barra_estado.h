#pragma once

#include "../../shared/font.h"
#include "../componentes/componente.h"
#include <SFML/Graphics/Drawable.hpp>

namespace sf {
    class Font;
    class RenderTarget;
    class Time;
} // namespace sf

class Etiqueta;

class EtiquetasBarraEstado : public ComponenteConFont {

  private:
    std::shared_ptr<Etiqueta> etiqueta;

  public:
    EtiquetasBarraEstado();
    void actualizar(const sf::Time &, const sf::Time &);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
