#pragma once

#include "../modelo/modelo.h"
#include "../shared.h"
#include "barras_progreso.h"
#include "componentes/varios.h"
#include <vector>

enum class IndicePanel;

struct Paneles : public sf::Drawable {
    std::map<IndicePanel, sf::RectangleShape> contenido;

    Paneles();
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

struct TitulosPaneles : public ObjetoConFont, public sf::Drawable {
    std::map<IndicePanel, sf::Text> contenido;
    TitulosPaneles(const sf::Font &);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

struct PanelesCompletos : public ObjetoConFont, public sf::Drawable {
    Paneles paneles;
    TitulosPaneles titulos_paneles;
    std::vector<BarraProgresoConNombre> barras_progreso_con_nombres;
    bool visible = false;

    PanelesCompletos(const sf::Font &);

    void actualizar(const EstadoPreparacionPizzas & //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
