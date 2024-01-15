#pragma once

#include "../modelo/modelo.h"
#include "../shared.h"
#include "barras_progreso.h"
#include "componentes/varios.h"
#include <vector>

enum class IndicePanel;

struct PanelCompleto : public sf::Drawable {
    IndicePanel indice;
    sf::RectangleShape forma;
    sf::Text etiqueta_titulo;
    PanelCompleto(IndicePanel indice, sf::Text etiqueta);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

struct PanelesCompletos : public ObjetoConFont, public sf::Drawable {
    std::map<IndicePanel, PanelCompleto> contenido;

    std::vector<BarraProgresoConNombre> barras_progreso_con_nombres;
    bool visible = false;

    PanelesCompletos(const sf::Font &);

    void actualizar(const VistaPreparacionPizzas & //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
