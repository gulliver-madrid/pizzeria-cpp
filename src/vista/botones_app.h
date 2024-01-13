#pragma once

#include "../modelo/dominio.h"
#include "componentes/boton_con_texto.h"

namespace modelo {
    enum class TipoPizza;
}

using TipoPizzaToBoton = std::map<dominio::TipoPizza, BotonConTexto>;

struct BotonesGenerales {
    BotonConTexto alternar_grid;
    BotonConTexto reiniciar;
    BotonConTexto salir;
    const std::vector<BotonConTexto *> obtener_todos();
};

class BotonesApp : public sf::Drawable {
  private:
    std::vector<BotonConTexto *> todos;
    void _establecer_todos();

  public:
    BotonConTexto empezar;
    TipoPizzaToBoton encargar;
    TipoPizzaToBoton despachar;
    BotonesGenerales generales;

    BotonesApp(
        const sf::Font &font, const dominio::TiposDePizza &tp_disponibles
    );
    void mostrar_botones_nivel(bool nuevo_valor);
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
