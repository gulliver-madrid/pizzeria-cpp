#pragma once

#include "componentes/componente.h"
#include "vista_shared.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

class Etiqueta;

///////////////////////////////////////////
// TarjetaPedido
//////////////////////////////////////////

class TarjetaPedido : public ComponenteConFont {
  public:
    std::vector<std::shared_ptr<Etiqueta>> etiquetas;
    sf::RectangleShape shape;

    TarjetaPedido(std::vector<std::shared_ptr<Etiqueta>>, sf::RectangleShape);
    void set_position(float pos_x, float pos_y);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// TarjetasPedidos
//////////////////////////////////////////

/*
 * Contiene los elementos visuales que muestran los pedidos.
 */
class TarjetasPedidos : public ComponenteConFont {

  private:
    std::vector<std::shared_ptr<TarjetaPedido>> _tarjetas;

  public:
    TarjetasPedidos();
    void actualizar(const VistaPedidos &);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
