#pragma once

#include "../../shared.h"
#include <SFML/Graphics/Text.hpp>

namespace sf {
    class Font;
    class RenderWindow;
} // namespace sf

struct Tiempo;
struct TiempoJuego;

struct EtiquetasBarraEstado : public ObjetoConFont {

  private:
    sf::Text etiqueta;

  public:
    EtiquetasBarraEstado(const sf::Font &);
    void actualizar(const Tiempo &, const TiempoJuego &);
    void dibujar(sf::RenderWindow &ventana) const;
};
