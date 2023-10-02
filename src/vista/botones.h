#pragma once

#include "componentes.h"

enum class TipoPizza;
struct BotonData;

BotonConTexto crearBotonConTexto(
    const BotonData &boton_data,  //
    const sf::Vector2i &posicion, //
    const sf::Font &font,         //
    float escala = 1
);

struct Botones {
  private:
    std::vector<BotonConTexto *> todos;

  public:
    BotonConTexto empezar;
    std::map<TipoPizza, BotonConTexto> encargar;
    std::map<TipoPizza, BotonConTexto> despachar;
    BotonConTexto reiniciar;
    BotonConTexto salir;

    Botones(const sf::Font &font, const std::vector<TipoPizza> &tp_disponibles);
    void dibujar(sf::RenderWindow &ventana) const;
    void mostrar_botones_nivel(bool nuevo_valor);
};
