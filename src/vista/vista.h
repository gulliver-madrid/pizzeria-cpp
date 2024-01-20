#pragma once

#include "../modelo/modelo.h"
#include "botones_app.h"
#include "etiquetas/etiquetas.h"
#include "paneles.h"
#include "presentacion_vista.h"

enum class FaseNivel;
struct Grid;

namespace sf {
    class RenderTarget;
    class Time;
} // namespace sf

// ActivacionBotones
struct ActivacionBotones {
    bool encargar;
    std::map<dominio::TipoPizza, bool> despachar;
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
    // provisional
    bool _deben_dibujarse_etiquetas_pedidos;
    bool _mostrando_grid = false;

    void _actualizar_etiquetas(
        std::optional<modelo::Pedidos> &info_pedidos, //
        const sf::Time &tiempo_real_actual,           //
        const sf::Time &tiempo_juego_actual           //
    );

    void _actualizar_vista_paneles( //
        const std::optional<VistaPreparacionPizzas> &vista_preparacion,
        const std::optional<PizzasToStrings> &vista_preparadas
    );

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
    void set_presentacion_vista(           //
        std::shared_ptr<PresentacionVista> //
    );

    void actualizar_interfaz_grafico(
        bool mostrando_grid,
        FaseNivel fase_actual,                            //
        const std::optional<VistaPreparacionPizzas> &,    //
        std::optional<PizzasToStrings> &vista_preparadas, //
        std::optional<modelo::Pedidos> &info_pedidos,     //
        const sf::Time &tiempo_real_actual,               //
        const sf::Time &tiempo_juego_actual               //
    );

    void mostrar_elementos_fase_activa();
    void esconder_botones_gestion_pizzeria();
    void activar_botones_condicionalmente(
        const ActivacionBotones &activacion_botones //
    );

    virtual std::shared_ptr<PanelesObservables> get_paneles() const override;

    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
