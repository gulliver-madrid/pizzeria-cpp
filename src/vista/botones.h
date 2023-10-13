#pragma once

#include "componentes/boton_con_texto.h"

enum class TipoPizza;
struct BotonData;

enum class Align { //
    Left,
    Right
};

BotonConTexto crearBotonConTexto(
    const BotonData &boton_data,  //
    const sf::Vector2f &posicion, //
    const sf::Font &font,         //
    Align align = Align::Left,    //
    double escala = 1             //
);

struct Botones {
  private:
    std::vector<BotonConTexto *> todos;

  public:
    BotonConTexto empezar;
    std::map<TipoPizza, BotonConTexto> encargar;
    std::map<TipoPizza, BotonConTexto> despachar;
    BotonConTexto alternar_grid;
    BotonConTexto reiniciar;
    BotonConTexto salir;

    Botones(const sf::Font &font, const std::vector<TipoPizza> &tp_disponibles);
    void dibujar(sf::RenderWindow &ventana) const;
    void mostrar_botones_nivel(bool nuevo_valor);
};
