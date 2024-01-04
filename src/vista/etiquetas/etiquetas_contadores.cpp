#include "etiquetas_contadores.h"
#include "../../modelo/modelo.h"
#include "../../templates/dibujar_elementos.h"
#include "../basicos_vista.h"
#include "../componentes/varios.h"
#include "../presentador.h"
#include "fabrica_etiquetas_contadores.h"
#include <iostream>

namespace medidas {
    constexpr int SEPARACION_VERTICAL_ENTRE_PEDIDOS = 24;
} // namespace medidas

namespace {

    float get_bottom(const sf::FloatRect &rect) { //
        return rect.top + rect.height;
    }

    const int top_left_padding = 5;

    /* Builds the shape of PedidoCard */
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

    /* Builds a PedidoCard */
    PedidoCard build_pedido_card(
        std::string texto, const sf::Font &font, size_t num_items //
    ) {
        static const auto tamano_fuente = 22;
        const auto etiqueta = sf::Text(texto, font, tamano_fuente);
        const auto shape = build_card_pedido_shape(num_items);
        return {etiqueta, shape};
    }

    void actualizar_card_pedidos(
        const modelo::Pedidos &pedidos,         //
        std::vector<PedidoCard> &cards_pedidos, //
        const sf::Font &font                    //
    ) {
        // Creamos las tarjetas de los pedidos
        cards_pedidos.clear();
        for (auto &pedido : pedidos) {
            const auto texto = presentador::pedido_to_string(pedido);
            const size_t num_items = pedido.contenido.size();
            const PedidoCard card = build_pedido_card(texto, font, num_items);
            cards_pedidos.emplace_back(card);
        }
        assert(cards_pedidos.size() == pedidos.size());

        // Les asignamos su posicion correcta
        const auto separacion_vertical =
            medidas::SEPARACION_VERTICAL_ENTRE_PEDIDOS;

        // Calcula la posicion del primer pedido
        const auto pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_PEDIDOS
        );
        float pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
        float pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;

        for (auto &card : cards_pedidos) {
            card.setPosition(pos_x, pos_y);
            //  Calcula la posicion del siguiente pedido
            const auto g_bounds = card.label.getGlobalBounds();
            pos_y = get_bottom(g_bounds) + separacion_vertical;
        }
    }
} // namespace

///// PedidoCard (public) /////

void PedidoCard::setPosition(float pos_x, float pos_y) {
    label.setPosition(pos_x, pos_y);
    shape.setPosition(pos_x - top_left_padding, pos_y - top_left_padding);
}

///// EtiquetasContadores (private) /////

void EtiquetasContadores::_actualizar_pedidos_dinamicos( //
    const modelo::Pedidos &pedidos
) {
    actualizar_card_pedidos(pedidos, cards_pedidos, font);
}

///// EtiquetasContadores (public) /////

EtiquetasContadores::EtiquetasContadores(const sf::Font &font)
    : ObjetoConFont(font) {}

void EtiquetasContadores::setup(const dominio::TiposDePizza &tp_disponibles) {
    FabricaEtiquetasContadores fabrica(font);
    int i = 0;
    for (auto tp : tp_disponibles) {
        etiquetas_preparadas.emplace(
            tp, fabrica.crearEtiquetaPizzasPreparadas(i)
        );
        i++;
    }
};

void EtiquetasContadores::actualizar(
    const modelo::PizzasAContadores &pizzas_a_contadores, //
    const modelo::Pedidos &pedidos                        //
) {
    for (auto &[tp, contadores_tp] : pizzas_a_contadores) {
        auto &nombre_pizza = tipo_pizza_to_string.at(tp);
        std::string linea =
            nombre_pizza + ": " + std::to_string(contadores_tp.preparadas);
        etiquetas_preparadas.at(tp).setString(linea);
    }

    _actualizar_pedidos_dinamicos(pedidos);
}

void EtiquetasContadores::dibujar(sf::RenderWindow &ventana) const {
    dibujar_elementos(ventana, etiquetas_preparadas);
    dibujar_elementos(ventana, etiquetas_servidas);
    dibujar_elementos(ventana, cards_pedidos);
}
