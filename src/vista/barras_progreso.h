#pragma once

#include <SFML/Graphics.hpp>

struct EstadoPreparacionPizzas;

struct BarraProgreso {
  private:
    sf::Vector2f dimensiones = {0, 0};

  public:
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
    void setup(const sf::Vector2f &dimensiones_, const sf::Vector2f &posicion);
    void update(int porcentaje);
};
struct BarraProgresoConNombre {
    sf::Text etiqueta;
    BarraProgreso bp;
};

std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, const sf::Font &font
);
