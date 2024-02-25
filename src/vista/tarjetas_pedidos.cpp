#include "tarjetas_pedidos.h"
#include "../shared/log_init.h"
#include "../templates/dibujar_elementos.h"
#include "../templates/helpers.h"
#include "basicos_vista.h"
#include "componentes/crear_etiqueta.h"
#include "componentes/etiqueta.h"
#include "presentaciones.h"
#include "vista_shared.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>

namespace medidas {
    namespace pedidos {
        constexpr float SEPARACION_VERTICAL = 30;
        constexpr int TAMANO_FUENTE = 22;
    } // namespace pedidos
} // namespace medidas

namespace colores {
    const sf::Color CardFillColor = {46, 134, 193};
    namespace card_outline {
        const sf::Color no_completo = sf::Color::Blue;
        const sf::Color completo = sf::Color::Green;
    } // namespace card_outline
} // namespace colores

namespace {

    float get_bottom(const sf::FloatRect &rect) { //
        return rect.top + rect.height;
    }

    const float top_left_padding = 5;

    sf::Color get_outline_color(bool completo) {
        if (completo) {
            return colores::card_outline::completo;
        }
        return colores::card_outline::no_completo;
    }

    sf::Vector2f get_size(size_t num_lineas) {
        const auto height = 30 + 26 * (static_cast<int>(num_lineas) - 1);
        return {
            static_cast<float>(250 + top_left_padding),   //
            static_cast<float>(height + top_left_padding) //
        };
    }

    /* Builds the shape of TarjetaPedido */
    sf::RectangleShape
    build_card_pedido_shape(size_t num_lineas, bool esta_cubierto) {
        assert(num_lineas > 0);
        auto shape = sf::RectangleShape{};
        shape.setOutlineThickness(5);
        shape.setOutlineColor(get_outline_color(esta_cubierto));
        shape.setFillColor(colores::CardFillColor);
        shape.setSize(get_size(num_lineas));
        return shape;
    }

    /* Construye una TarjetaPedido */
    TarjetaPedido construye_tarjeta_pedido(
        const VistaPedido &vista_pedido, size_t num_lineas //
    ) {
        static const auto tamano_fuente = medidas::pedidos::TAMANO_FUENTE;
        std::vector<std::shared_ptr<Etiqueta>> etiquetas;
        for (auto &linea : vista_pedido.lineas) {
            const auto etiqueta = crear_etiqueta( //
                linea.cadena, tamano_fuente, "etiqueta pedido"
            );
            if (linea.esta_cubierta) {
                etiqueta->set_color(sf::Color::Green);
            }
            etiquetas.emplace_back(etiqueta);
        }
        const auto shape = build_card_pedido_shape( //
            num_lineas, vista_pedido.esta_cubierto()
        );
        return {etiquetas, shape};
    }

    void actualizar_tarjetas_pedidos(
        const PresentacionPedidos &presentacion_pedidos,      //
        std::vector<std::shared_ptr<TarjetaPedido>> &tarjetas //
    ) {
        // TODO:actualizar solo si cambian
        // Creamos las tarjetas de los pedidos
        tarjetas.clear();
        for (auto &vista_pedido : presentacion_pedidos) {
            const size_t num_lineas = vista_pedido.get_num_lineas();
            const auto tarjeta = std::make_shared<TarjetaPedido>(
                construye_tarjeta_pedido(vista_pedido, num_lineas)
            );
            tarjetas.emplace_back(tarjeta);
        }
        assert(tarjetas.size() == presentacion_pedidos.size());
    }

    sf::Vector2f obtener_posicion_inicial() {
        // Calcula la posicion del primer pedido
        const auto pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_PEDIDOS
        );
        float pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
        float pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
        return {pos_x, pos_y};
    }

    float calcular_posicion_vertical_siguiente_tarjeta( //
        std::shared_ptr<TarjetaPedido> tarjeta
    ) {
        static const auto separacion_vertical =
            medidas::pedidos::SEPARACION_VERTICAL;
        const auto &ultima_etiqueta = obtener_ultimo(tarjeta->etiquetas);
        const auto g_bounds = ultima_etiqueta->get_global_bounds();
        return get_bottom(g_bounds) + separacion_vertical;
    }

    void establece_posicion_tarjetas(
        std::vector<std::shared_ptr<TarjetaPedido>> &tarjetas //
    ) {
        auto [pos_x, pos_y] = obtener_posicion_inicial();
        for (auto &tarjeta : tarjetas) {
            tarjeta->set_position(pos_x, pos_y);
            pos_y = calcular_posicion_vertical_siguiente_tarjeta(tarjeta);
        }
    }

} // namespace

///////////////////////////////////////////
// TarjetaPedido (public)
//////////////////////////////////////////

TarjetaPedido::TarjetaPedido(
    std::vector<std::shared_ptr<Etiqueta>> etiquetas_, sf::RectangleShape shape
)
    : etiquetas(etiquetas_), shape(shape) {
    for (auto &etiqueta : etiquetas) {
        add_child(etiqueta);
    }
}

void TarjetaPedido::set_position(float pos_x, float pos_y) {
    assert(etiquetas.size() > 0);
    static const auto font_size = medidas::pedidos::TAMANO_FUENTE;
    for (size_t i = 0; i < etiquetas.size(); ++i) {
        etiquetas.at(i)->set_position(pos_x, pos_y + font_size * i);
    }
    shape.setPosition(pos_x - top_left_padding, pos_y - top_left_padding);
}

void TarjetaPedido::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    target.draw(shape);
    for (auto &etiqueta : etiquetas) {
        target.draw(*etiqueta);
    }
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
    establece_posicion_tarjetas(tarjetas_pedidos);
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
