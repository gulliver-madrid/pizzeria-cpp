#include "etiquetas_pedidos.h"
#include "../../modelo/control_pizzas.h"
#include "../../modelo/dominio.h"
#include "../../shared/log_init.h"
#include "../../templates/dibujar_elementos.h"
#include "../../templates/helpers.h"
#include "../basicos_vista.h"
#include "../componentes/etiqueta.h"
#include "../componentes/varios.h"
#include "../presentador.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>
#include <iostream>

namespace medidas {
    constexpr int SEPARACION_VERTICAL_ENTRE_PEDIDOS = 24;
} // namespace medidas

namespace {

    float get_bottom(const sf::FloatRect &rect) { //
        return rect.top + rect.height;
    }

    const int top_left_padding = 5;

    /* Builds the shape of TarjetaPedido */
    sf::RectangleShape build_card_pedido_shape(size_t num_items) {
        const int height = 30 + 26 * (num_items - 1);
        const auto size = sf::Vector2f(
            250 + top_left_padding,   //
            height + top_left_padding //
        );
        static const auto outline_color = sf::Color::Blue;
        static const auto fill_color = sf::Color(46, 134, 193);
        auto shape = sf::RectangleShape{};
        shape.setOutlineColor(outline_color);
        shape.setOutlineThickness(5);
        shape.setSize(size);
        shape.setFillColor(fill_color);
        return shape;
    }

    /* Construye una TarjetaPedido */
    TarjetaPedido construye_tarjeta_pedido(
        std::string texto, const OptionalFont &font, size_t num_items //
    ) {
        static const auto tamano_fuente = 22;
        const auto etiqueta = crear_etiqueta(texto, tamano_fuente, font);
        const auto shape = build_card_pedido_shape(num_items);
        return {etiqueta, shape};
    }

    void actualizar_tarjetas_pedidos(
        const modelo::Pedidos &pedidos,       //
        std::vector<TarjetaPedido> &tarjetas, //
        const OptionalFont &font              //
    ) {
        // Creamos las tarjetas de los pedidos
        tarjetas.clear();
        for (auto &pedido : pedidos) {
            const auto texto = presentador::pedido_to_string(pedido);
            const size_t num_items = pedido.contenido.size();
            const TarjetaPedido card =
                construye_tarjeta_pedido(texto, font, num_items);
            tarjetas.emplace_back(card);
        }
        assert(tarjetas.size() == pedidos.size());

        // Les asignamos su posicion correcta
        const auto separacion_vertical =
            medidas::SEPARACION_VERTICAL_ENTRE_PEDIDOS;

        // Calcula la posicion del primer pedido
        const auto pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_PEDIDOS
        );
        float pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
        float pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;

        for (auto &card : tarjetas) {
            card.set_position(pos_x, pos_y);
            //  Calcula la posicion del siguiente pedido
            const auto g_bounds = card.label->get_global_bounds();
            pos_y = get_bottom(g_bounds) + separacion_vertical;
        }
    }
} // namespace

///////////////////////////////////////////
// TarjetaPedido (public)
//////////////////////////////////////////

TarjetaPedido::TarjetaPedido(
    std::shared_ptr<Etiqueta> label, sf::RectangleShape shape
)
    : label(label), shape(shape) {}

void TarjetaPedido::set_position(float pos_x, float pos_y) {
    label->set_position(pos_x, pos_y);
    shape.setPosition(pos_x - top_left_padding, pos_y - top_left_padding);
}

void TarjetaPedido::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    target.draw(shape);
    target.draw(*label);
}

///////////////////////////////////////////
// EtiquetasPedidos (private)
//////////////////////////////////////////

void EtiquetasPedidos::_actualizar_vista_pedidos( //
    const modelo::Pedidos &pedidos
) {
    actualizar_tarjetas_pedidos(pedidos, tarjetas_pedidos, font);
}

///////////////////////////////////////////
// EtiquetasPedidos (public)
//////////////////////////////////////////

EtiquetasPedidos::EtiquetasPedidos() {}

void EtiquetasPedidos::actualizar(const modelo::Pedidos &pedidos //
) {
    _actualizar_vista_pedidos(pedidos);
}

void EtiquetasPedidos::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    dibujar_elementos(target, tarjetas_pedidos);
}
