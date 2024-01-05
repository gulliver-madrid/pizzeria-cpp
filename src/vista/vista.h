#pragma once

#include "../modelo/modelo.h"
#include "botones_app.h"
#include "etiquetas/etiquetas.h"
#include "paneles.h"

struct Estado;
struct Grid;

namespace impl {
    VistaPizzasToStrings contadores_to_preparadas( //
        const modelo::PizzasAContadores &
    );
} // namespace impl

///// Vista /////

class Vista : public ObjetoConFont {
  private:
    const dominio::TiposDePizza &tp_disponibles;

    void _actualizar_y_dibujar_paneles(
        sf::RenderTarget &(target),                //
        PanelesCompletos &paneles_completos,       //
        const EstadoPreparacionPizzas &preparacion //
    );

  public:
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
        const NumNivel &                  //
    );

    void actualizarIU(
        sf::RenderTarget &,                //
        const Estado &,                    //
        const sf::Time &tiempo_real_actual //
    );
    void mostrar_elementos_fase_activa();
    void esconder_botones_gestion_pizzeria();
};
