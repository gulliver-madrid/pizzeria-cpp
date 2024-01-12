#pragma once

#include "../modelo/modelo.h"
#include "../modelo_amplio/modelo_amplio.h"
#include "botones_app.h"
#include "etiquetas/etiquetas.h"
#include "paneles.h"
#include "presentacion_vista.h"

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

///// Vista /////

class Vista : public ObjetoConFont, public sf::Drawable {
  private:
    const dominio::TiposDePizza &tp_disponibles;

    void _actualizar_paneles(const EstadoPreparacionPizzas &);
    void _dibujar_paneles(sf::RenderTarget &target) const;
    void _actualizar_vista_paneles(
        const EstadoPreparacionPizzas &preparacion, sf::RenderTarget &target
    );

  public:
    std::shared_ptr<PresentacionVista> presentacion_vista;
    BotonesApp botones;
    PanelesCompletos paneles_completos;
    EtiquetasGenerales etiquetas;
    Grid &grid;

    Vista(
        const sf::Font &font,                       //
        Grid &grid,                                 //
        const dominio::TiposDePizza &tp_disponibles //
    );

    void setup(
        const std::string &instrucciones, //
        const NumNivel &
    );
    void set_presentacion_vista(           //
        std::shared_ptr<PresentacionVista> //
    );

    void actualizarIU(
        sf::RenderTarget &target,          //
        const ModeloAmplio &modelo_amplio, //
        const sf::Time &tiempo_real_actual //
    );

    void mostrar_elementos_fase_activa();
    void esconder_botones_gestion_pizzeria();
    void activar_botones_condicionalmente(
        const ActivacionBotones &activacion_botones //
    );

    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
