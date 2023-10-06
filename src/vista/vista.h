#pragma once

#include "botones.h"
#include "etiquetas.h"
#include "paneles.h"

struct Estado;
struct Grid;

struct Vista {
  private:
    const sf::Font &font;
    const std::vector<TipoPizza> &tp_disponibles;
    void actualizar_paneles(
        sf::RenderWindow &ventana,           //
        PanelesCompletos &paneles_completos, //
        const Encargos &encargos             //
    );

  public:
    Botones botones;
    PanelesCompletos paneles_completos;
    EtiquetasGenerales etiquetas;
    Grid &grid;

    Vista(
        bool es_estatico,                            //
        const sf::Font &font,                        //
        Grid &grid,                                  //
        const std::vector<TipoPizza> &tp_disponibles //
    )
        : botones(font, tp_disponibles), //
          paneles_completos(font),       //
          etiquetas(es_estatico, font),  //
          grid(grid),                    //
          font(font),                    //
          tp_disponibles(tp_disponibles) {}

    void setup(
        const std::string &instrucciones, //
        NumNivel num_nivel,               //
        int total_objetivos               //
    );

    void actualizarIU(             //
        sf::RenderWindow &ventana, //
        const Estado &estado       //
    );
    void procesa_cambio_de_fase(FaseNivel nueva_fase);
};
