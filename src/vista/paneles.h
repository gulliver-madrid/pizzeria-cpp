#pragma once

#include "../modelo/modelo.h"
#include "../shared/font.h"
#include "barras_progreso.h"
#include "componentes/varios.h"
#include "etiquetas/etiquetas_contadores.h"
#include <vector>

enum class IndicePanel;

///////////////////////////////////////////
// Panel
/////////////////////////////////////////

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

///////////////////////////////////////////
// PanelEnPreparacion
/////////////////////////////////////////

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

///////////////////////////////////////////
// PanelPreparadas
/////////////////////////////////////////

struct PanelPreparadas : public Panel, public ComponenteConFont {
    std::shared_ptr<EtiquetasPreparadas> etiquetas_preparadas;
    PanelPreparadas::PanelPreparadas(IndicePanel indice, sf::Text etiqueta);
    void setup(const dominio::TiposDePizza &tp_disponibles);
    void actualizar(const PizzasToStrings &vista_preparadas);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};

///////////////////////////////////////////
// PanelesObservables
/////////////////////////////////////////

class PanelesObservables {
  public:
    virtual bool get_visibilidad() const { //
        return false;
    };
};

///////////////////////////////////////////
// Paneles
/////////////////////////////////////////

class Paneles : public ObjetoConFont,
                public sf::Drawable,
                public PanelesObservables {
  private:
    std::map<IndicePanel, std::unique_ptr<Panel>> _paneles;

  public:
    bool visible = false;

    Paneles(const dominio::TiposDePizza &tp_disponibles, const OptionalFont &);

    void Paneles::actualizar(                            //
        const VistaPreparacionPizzas &vista_preparacion, //
        const PizzasToStrings &vista_preparadas          //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
