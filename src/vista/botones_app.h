#pragma once

#include "../modelo/dominio.h"
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

struct BotonesApp {
  private:
    std::vector<BotonConTexto *> todos;
    void _establecer_todos();

  public:
    BotonConTexto empezar;
    TipoPizzaToBoton encargar;
    TipoPizzaToBoton despachar;
    BotonesGenerales generales;

    BotonesApp(
        const sf::Font &font, const modelo::TiposDePizza &tp_disponibles
    );
    void dibujar(sf::RenderWindow &ventana) const;
    void mostrar_botones_nivel(bool nuevo_valor);
};