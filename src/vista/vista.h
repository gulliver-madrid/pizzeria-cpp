#pragma once

#include "botones_app.h"
#include "etiquetas/etiquetas.h"
#include "paneles.h"

struct Estado;
struct Grid;
namespace sf {
    struct Time;
}

class Vista : public ObjetoConFont {
    const dominio::TiposDePizza &tp_disponibles;
    void actualizar_paneles(
        sf::RenderWindow &ventana,                 //
        PanelesCompletos &paneles_completos,       //
        const EstadoPreparacionPizzas &preparacion //
    );

  public:
    BotonesApp botones;
    PanelesCompletos paneles_completos;
    EtiquetasGenerales etiquetas;
    Grid &grid;

    Vista(
        const EsSistemaEstatico &es_estatico,       //
        const sf::Font &font,                       //
        Grid &grid,                                 //
        const dominio::TiposDePizza &tp_disponibles //
    );

    void setup(
        const std::string &instrucciones,          //
        const NumNivel &,                          //
        const std::optional<int> objetivo_estatico //
    );

    void actualizarIU(
        sf::RenderWindow &,                //
        const Estado &,                    //
        const sf::Time &tiempo_real_actual //
    );
    void mostrar_elementos_fase_activa();
    void esconder_botones_gestion_pizzeria();
};
