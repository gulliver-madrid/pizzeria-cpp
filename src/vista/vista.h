#pragma once

#include "../shared/num_nivel.h"
#include "componentes/componente.h"
#include "presentacion_vista.h"
#include "presentaciones.h"
#include "vista_shared.h"

class BotonesApp;
class EtiquetasGenerales;
class Grid;
class Paneles;
class PanelesObservables;

namespace sf {
    class Time;
} // namespace sf

/* Contiene la informacion relativa a que botones deben estar activados */
struct ActivacionBotones {
    bool encargar;
    std::map<dominio::TipoPizza, bool> despachar;
};

struct VistasJuego {
    std::optional<PresentacionPreparacionPizzas> info_preparacion;
    std::optional<PizzasToStrings> info_preparadas;
    std::optional<const PresentacionPedidos> info_pedidos;
};

struct PresentacionGeneral {
    bool mostrando_grid;
    const VistasJuego &vistas;
    VistaBarraEstado &barra_estado;
};

class VistaObservable {
  public:
    virtual std::shared_ptr<PanelesObservables> get_paneles() const = 0;
};

///////////////////////////////////////////
// Vista
//////////////////////////////////////////

class Vista : public ComponenteConFont, public VistaObservable {
  private:
    bool _mostrando_grid = false;

    void _actualizar_etiquetas(const VistaBarraEstado &);

    void _actualizar_vista_paneles(const VistasJuego &);

  public:
    std::shared_ptr<PresentacionVista> presentacion_vista;
    std::shared_ptr<BotonesApp> botones;
    std::shared_ptr<Paneles> paneles;
    std::shared_ptr<EtiquetasGenerales> etiquetas;
    std::shared_ptr<Grid> grid;

    Vista();

    void setup(
        std::shared_ptr<Grid>,                       //
        const dominio::TiposDePizza &tp_disponibles, //
        const std::string &instrucciones,            //
        const NumNivelOpcional &                     //
    );

    void actualizar_interfaz_grafico(const PresentacionGeneral &);
    void cambiar_visibilidad_instrucciones(bool);
    void cambiar_visibilidad_resultado(bool);
    void mostrar_elementos_fase_activa();
    void esconder_botones_gestion_pizzeria();
    void activar_botones_condicionalmente(
        const ActivacionBotones &activacion_botones //
    );

    std::shared_ptr<const PresentacionVista> get_presentacion_vista() const;
    virtual std::shared_ptr<PanelesObservables> get_paneles() const override;

    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
