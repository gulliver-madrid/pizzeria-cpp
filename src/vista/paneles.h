#pragma once

#include "../modelo/modelo.h"
#include "../shared/font.h"
#include "barras_progreso.h"
#include "componentes/crear_etiqueta.h"
#include "etiquetas/etiquetas_preparadas.h"
#include "paneles_observables.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <memory>
#include <vector>

class BotonConTexto;
class Etiqueta;
class TarjetasPedidos;
enum class IndicePanel;

struct VistasPaneles {
    PresentacionPreparacionPizzas info_preparacion;
    PizzasToStrings info_preparadas;
    VistaPedidos info_pedidos;
};

///////////////////////////////////////////
// Panel
/////////////////////////////////////////

class Panel : public ComponenteConFont {
  public:
    IndicePanel indice;
    sf::RectangleShape forma;
    std::shared_ptr<Etiqueta> etiqueta_titulo;
    Panel(IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// PanelEncargar
/////////////////////////////////////////

class PanelEncargar : public Panel {
  private:
    std::shared_ptr<sf::RenderTexture> render_texture;

  public:
    TipoPizzaToBoton encargar;
    PanelEncargar(
        IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta,
        const dominio::TiposDePizza &tp_disponibles
    );
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// PanelEnPreparacion
/////////////////////////////////////////

class PanelEnPreparacion : public Panel {
  public:
    std::vector<std::shared_ptr<BarraProgresoConNombre>>
        barras_progreso_con_nombres;
    PanelEnPreparacion(IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta);
    void actualizar(const PresentacionPreparacionPizzas &info_preparacion //
    );
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// PanelPreparadas
/////////////////////////////////////////

class PanelPreparadas : public Panel {
  public:
    TipoPizzaToBoton despachar;
    std::shared_ptr<EtiquetasPreparadas> etiquetas_preparadas;
    PanelPreparadas::PanelPreparadas(
        IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta,
        const dominio::TiposDePizza &tp_disponibles
    );
    void actualizar(const PizzasToStrings &info_preparadas);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// PanelPedidos
/////////////////////////////////////////

class PanelPedidos : public Panel {
  private:
    std::shared_ptr<sf::RenderTexture> render_texture;

  public:
    std::shared_ptr<TarjetasPedidos> tarjetas_pedidos;

    PanelPedidos::PanelPedidos(
        IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta_titulo
    );

    void actualizar( //
        const VistaPedidos &presentacion_pedidos
    );
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// Paneles
/////////////////////////////////////////

class Paneles : public ComponenteConFont, public PanelesObservables {
  private:
    std::map<IndicePanel, std::shared_ptr<Panel>> _paneles;

  public:
    bool visible = false;

    Paneles(const dominio::TiposDePizza &tp_disponibles);

    std::shared_ptr<PanelEncargar> get_panel_encargar();
    std::shared_ptr<PanelPreparadas> get_panel_preparadas();
    void actualizar(const std::shared_ptr<const VistasPaneles>);
    virtual bool get_visibilidad() const override;
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
    std::shared_ptr<Panel> getPanel(IndicePanel indice) const {
        return _paneles.at(indice);
    }
    virtual bool colisiona(IndicePanel, const sf::Vector2i &) const;
};
