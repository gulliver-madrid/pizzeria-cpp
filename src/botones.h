#pragma once

#include "componentes.h"
#include "modelo/dominio.h"

BotonConTexto crearBotonConTexto(
    const std::string &, const sf::Color &color_fondo, const sf::Vector2i &,
    const sf::Font &, const sf::Color &color_texto = sf::Color::White,
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

    Botones(sf::Font &);
    void dibujar(sf::RenderWindow &ventana) const;
};
