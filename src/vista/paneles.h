#pragma once

#include "../modelo/modelo.h"
#include "barras_progreso.h"
#include "componentes/varios.h"
#include <vector>

enum class IndicePanel;

struct Paneles {
    sf::RectangleShape encargar;
    sf::RectangleShape en_preparacion;
    sf::RectangleShape preparadas;
    sf::RectangleShape pedidos;

    Paneles();
    void dibujar(sf::RenderWindow &window);
};

struct TitulosPaneles {
    sf::Text encargar;
    sf::Text en_preparacion;
    sf::Text preparadas;
    sf::Text pedidos;

    void dibujar(sf::RenderWindow &window);
};

struct PanelesCompletos {
    const sf::Font &font;
    Paneles paneles;
    TitulosPaneles titulos_paneles;
    std::vector<BarraProgresoConNombre> barras_progreso_con_nombres;
    bool visible = false;

    PanelesCompletos(const sf::Font &font);
    void dibujar(
        sf::RenderWindow &ventana,                 //
        const EstadoPreparacionPizzas &preparacion //
    );
};
