#pragma once

#include "../../shared/font.h"
#include "../componentes/componente.h"
#include "../presentaciones.h"
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
    void actualizar(const VistaBarraEstado &info_barra_estado);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
