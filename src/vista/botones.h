#pragma once

#include "componentes/boton_con_texto.h"

enum class TipoPizza;

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
    std::map<TipoPizza, BotonConTexto> encargar;
    std::map<TipoPizza, BotonConTexto> despachar;
    BotonesGenerales generales;

    Botones(const sf::Font &font, const std::vector<TipoPizza> &tp_disponibles);
    void dibujar(sf::RenderWindow &ventana) const;
    void mostrar_botones_nivel(bool nuevo_valor);
};
