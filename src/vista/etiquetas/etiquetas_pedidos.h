#pragma once

#include "../componente.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

class Etiqueta;
class Pedido;

namespace dominio {
    enum class TipoPizza;
}
namespace modelo {
    using Pedidos = std::vector<Pedido>;
} // namespace modelo
namespace sf {
    class RenderTarget;
}

///////////////////////////////////////////
// TarjetaPedido
//////////////////////////////////////////

class TarjetaPedido : public ComponenteConFont {
  public:
    std::shared_ptr<Etiqueta> etiqueta;
    sf::RectangleShape shape;

    TarjetaPedido(std::shared_ptr<Etiqueta>, sf::RectangleShape);
    void set_position(float pos_x, float pos_y);
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// EtiquetasPedidos
//////////////////////////////////////////

/*
 * Contiene los elementos visuales que muestran los pedidos.
 */
class EtiquetasPedidos : public ComponenteConFont {
    using TipoPizza = dominio::TipoPizza;

  private:
    void _actualizar_vista_pedidos(
        const std::vector<std::pair<std::string, size_t>> &presentacion_pedidos
    );

  public:
    std::vector<std::shared_ptr<TarjetaPedido>> tarjetas_pedidos;

    EtiquetasPedidos();
    void actualizar(
        const std::vector<std::pair<std::string, size_t>> &presentacion_pedidos
    );
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
