#pragma once

#include "../modelo/modelo.h"
#include "../shared.h"
#include "barras_progreso.h"
#include "componentes/varios.h"
#include <vector>

enum class IndicePanel;

struct Paneles {
    std::map<IndicePanel, sf::RectangleShape> contenido;

    Paneles();
    void dibujar(sf::RenderWindow &);
};

struct TitulosPaneles : public ObjetoConFont {
    std::map<IndicePanel, sf::Text> contenido;
    TitulosPaneles(const sf::Font &);
    void dibujar(sf::RenderWindow &);
};

struct PanelesCompletos : public ObjetoConFont {
    Paneles paneles;
    TitulosPaneles titulos_paneles;
    std::vector<BarraProgresoConNombre> barras_progreso_con_nombres;
    bool visible = false;

    PanelesCompletos(const sf::Font &);
    void dibujar(
        sf::RenderWindow &,             //
        const EstadoPreparacionPizzas & //
    );
};
