#pragma once

#include "../modelo/modelo.h"
#include "componentes.h"
#include <vector>

enum class IndicePanel;

struct BarraProgreso {
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
};
struct BarraProgresoConNombre {
    sf::Text etiqueta;
    BarraProgreso bp;
};

struct Paneles {
    sf::RectangleShape encargar;
    sf::RectangleShape en_preparacion;
    sf::RectangleShape preparadas;
    sf::RectangleShape pedidos;

    Paneles();
    void dibujar(sf::RenderWindow &window);
};

std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, sf::Font &font
);

struct TitulosPaneles {
    sf::Text encargar;
    sf::Text en_preparacion;
    sf::Text preparadas;
    sf::Text pedidos;

    void dibujar(sf::RenderWindow &window);
};

struct PanelesCompletos {
    Paneles paneles;
    TitulosPaneles titulos_paneles;
    std::vector<BarraProgresoConNombre> barras_progreso_con_nombres;
    bool visible = false;

    PanelesCompletos(const sf::Font &font);
    void dibujar(
        sf::RenderWindow &ventana, const EstadoPreparacionPizzas &preparacion,
        const sf::Font &font
    );
};
