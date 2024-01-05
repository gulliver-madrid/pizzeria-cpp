#pragma once

#include "../../shared.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

namespace sf {
    class Font;
    class RenderTarget;
} // namespace sf

struct EtiquetasBarraEstado : public ObjetoConFont {

  private:
    sf::Text etiqueta;

  public:
    EtiquetasBarraEstado(const sf::Font &);
    void actualizar(const sf::Time &, const sf::Time &);
    void dibujar(sf::RenderTarget &target) const;
};
