#pragma once

#include <SFML/Graphics.hpp>

struct EstadoPreparacionPizzas;
enum class TipoPizza;

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
  private:
    sf::Text etiqueta;
    BarraProgreso bp;

  public:
    void setup(
        sf::Vector2f &dimensiones,    //
        const TipoPizza tp,           //
        const sf::Vector2f &posicion, //
        const sf::Font &font          //
    );
    void update(int porcentaje);
    void dibujar(sf::RenderWindow &ventana);
};

std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, const sf::Font &font
);
