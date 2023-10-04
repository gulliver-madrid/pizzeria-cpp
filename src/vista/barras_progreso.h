#pragma once

#include <SFML/Graphics.hpp>

struct EstadoPreparacionPizzas;

struct BarraProgreso {
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
    void setup(
        const sf::Vector2f &dimensiones, int porcentaje,
        const sf::Vector2f &posicion
    );
};
struct BarraProgresoConNombre {
    sf::Text etiqueta;
    BarraProgreso bp;
};

std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, const sf::Font &font
);
