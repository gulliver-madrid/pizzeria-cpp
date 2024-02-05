#include "etiquetas_pedidos.h"
#include "../../shared/log_init.h"
#include "../../templates/dibujar_elementos.h"
#include "../../templates/helpers.h"
#include "../basicos_vista.h"
#include "../componentes/crear_etiqueta.h"
#include "../componentes/etiqueta.h"
#include "../presentaciones.h"
#include "../vista_shared.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>

namespace medidas {
    constexpr float SEPARACION_VERTICAL_ENTRE_PEDIDOS = 24;
} // namespace medidas

namespace {

    float get_bottom(const sf::FloatRect &rect) { //
        return rect.top + rect.height;
    }

    const float top_left_padding = 5;

    /* Builds the shape of TarjetaPedido */
    sf::RectangleShape build_card_pedido_shape(size_t num_items) {
        assert(num_items > 0);
        const auto height = 30 + 26 * (static_cast<int>(num_items) - 1);
        const auto size = sf::Vector2f(
            static_cast<float>(250 + top_left_padding),   //
            static_cast<float>(height + top_left_padding) //
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
        std::string texto, size_t num_items //
    ) {
        static const auto tamano_fuente = 22;
        const auto etiqueta =
            crear_etiqueta(texto, tamano_fuente, "etiqueta pedidos");
        const auto shape = build_card_pedido_shape(num_items);
        return {etiqueta, shape};
    }

    void actualizar_tarjetas_pedidos(
        const PresentacionPedidos &presentacion_pedidos,      //
        std::vector<std::shared_ptr<TarjetaPedido>> &tarjetas //
    ) {
        // TODO:actualizar solo si cambian
        // Creamos las tarjetas de los pedidos
        tarjetas.clear();
        for (auto &vista_pedido : presentacion_pedidos) {
            const auto texto = unir_cadenas(vista_pedido.cadenas, "\n");
            const size_t num_items = vista_pedido.num_items;
            const auto tarjeta = std::make_shared<TarjetaPedido>(
                construye_tarjeta_pedido(texto, num_items)
            );
            tarjetas.emplace_back(tarjeta);
        }
        assert(tarjetas.size() == presentacion_pedidos.size());
    }

    void reposiciona_tarjetas(
        std::vector<std::shared_ptr<TarjetaPedido>> &tarjetas //
    ) {
        const auto separacion_vertical =
            medidas::SEPARACION_VERTICAL_ENTRE_PEDIDOS;
        // Calcula la posicion del primer pedido
        const auto pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_PEDIDOS
        );
        float pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
        float pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;

        for (auto &tarjeta : tarjetas) {
            tarjeta->set_position(pos_x, pos_y);
            //  Calcula la posicion del siguiente pedido
            const auto g_bounds = tarjeta->etiqueta->get_global_bounds();
            pos_y = get_bottom(g_bounds) + separacion_vertical;
        }
    }

} // namespace

///////////////////////////////////////////
// TarjetaPedido (public)
//////////////////////////////////////////

TarjetaPedido::TarjetaPedido(
    std::shared_ptr<Etiqueta> etiqueta_, sf::RectangleShape shape
)
    : etiqueta(etiqueta_), shape(shape) {
    add_child(etiqueta_);
}

void TarjetaPedido::set_position(float pos_x, float pos_y) {
    etiqueta->set_position(pos_x, pos_y);
    shape.setPosition(pos_x - top_left_padding, pos_y - top_left_padding);
}

void TarjetaPedido::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    target.draw(shape);
    target.draw(*etiqueta);
}

///////////////////////////////////////////
// EtiquetasPedidos (private)
//////////////////////////////////////////

void EtiquetasPedidos::_actualizar_vista_pedidos( //
    const PresentacionPedidos &presentacion_pedidos
) {
    for (auto tarjeta : tarjetas_pedidos) {
        remove_child(tarjeta);
    }
    actualizar_tarjetas_pedidos(presentacion_pedidos, tarjetas_pedidos);
    for (auto tarjeta : tarjetas_pedidos) {
        add_child(tarjeta);
    }
    reposiciona_tarjetas(tarjetas_pedidos);
}

///////////////////////////////////////////
// EtiquetasPedidos (public)
//////////////////////////////////////////

EtiquetasPedidos::EtiquetasPedidos() {}

void EtiquetasPedidos::actualizar(
    const PresentacionPedidos &presentacion_pedidos
) {
    _actualizar_vista_pedidos(presentacion_pedidos);
}

void EtiquetasPedidos::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    dibujar_elementos(target, tarjetas_pedidos);
}
