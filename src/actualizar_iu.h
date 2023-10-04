#pragma once

#include "vista/vista.h"

struct Estado;
struct Grid;

struct Vista {
  private:
    const sf::Font &font;
    const std::vector<TipoPizza> &tp_disponibles;

  public:
    Botones botones;
    PanelesCompletos paneles_completos;
    EtiquetasGenerales etiquetas;
    Grid &grid;
    Vista(
        const sf::Font &font, Grid &grid,
        const std::vector<TipoPizza> &tp_disponibles
    )
        : botones(font, tp_disponibles), paneles_completos(font), grid(grid),
          font(font), tp_disponibles(tp_disponibles) {}
    void setup(
        const std::string &instrucciones, //
        int num_nivel,                    //
        int total_objetivos
    );
    void actualizarIU(             //
        sf::RenderWindow &ventana, //
        const Estado &estado,      //
        sf::Font font              //
    );
};
