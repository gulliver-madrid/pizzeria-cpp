#pragma once

#include "componentes/boton_con_texto.h"

namespace modelo {
    enum class TipoPizza;
}

using TipoPizzaToBoton = std::map<modelo::TipoPizza, BotonConTexto>;

struct BotonesGenerales {
    BotonConTexto alternar_grid;
    BotonConTexto reiniciar;
    BotonConTexto salir;
    const std::vector<BotonConTexto *> obtener_todos();
};

struct Botones {
  private:
    std::vector<BotonConTexto *> todos;

  public:
    BotonConTexto empezar;
    TipoPizzaToBoton encargar;
    TipoPizzaToBoton despachar;
    BotonesGenerales generales;

    Botones(
        const sf::Font &font,
        const std::vector<modelo::TipoPizza> &tp_disponibles
    );
    void dibujar(sf::RenderWindow &ventana) const;
    void mostrar_botones_nivel(bool nuevo_valor);
};
