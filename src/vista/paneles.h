#pragma once

#include "../modelo/modelo.h"
#include "../shared/font.h"
#include "barras_progreso.h"
#include "componentes/varios.h"
#include <vector>

enum class IndicePanel;

struct Panel : public sf::Drawable {
    IndicePanel indice;
    sf::RectangleShape forma;
    sf::Text etiqueta_titulo;
    Panel(IndicePanel indice, sf::Text etiqueta);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

struct PanelEnPreparacion : public Panel, public ObjetoConFont {
    std::vector<BarraProgresoConNombre> barras_progreso_con_nombres;
    PanelEnPreparacion(
        IndicePanel indice, sf::Text etiqueta, const OptionalFont &font
    );
    void actualizar(const VistaPreparacionPizzas &vista_preparacion //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

class PanelesObservables {
  public:
    virtual bool get_visibilidad() const { //
        return false;
    };
};

class Paneles : public ObjetoConFont,
                public sf::Drawable,
                public PanelesObservables {
  private:
    std::map<IndicePanel, std::unique_ptr<Panel>> _paneles;

  public:
    bool visible = false;

    Paneles(const OptionalFont &);

    void actualizar(const VistaPreparacionPizzas & //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
