#pragma once

#include "../modelo/dominio.h"
#include "componentes.h"

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
    void mostrar_botones_nivel(bool nuevo_valor) {
        for (auto tp : tipos_de_pizza) {
            despachar[tp].visible = nuevo_valor;
            encargar[tp].visible = nuevo_valor;
        }
    }
};
