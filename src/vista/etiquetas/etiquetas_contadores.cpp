#include "etiquetas_contadores.h"
#include "../componentes/varios.h"
#include "../presentador.h"
#include "../vista_basics.h"
#include "fabrica_etiquetas_contadores.h"

namespace medidas {
    constexpr int SEPARACION_VERTICAL_ENTRE_PEDIDOS = 20;
} // namespace medidas

float get_bottom(const sf::FloatRect &rect) { //
    return rect.top + rect.height;
}

void EtiquetasContadores::setup(const std::vector<TipoPizza> &tp_disponibles) {
    FabricaEtiquetasContadores fabrica(font);
    int i = 0;
    for (auto &tp : tp_disponibles) {
        texto_preparadas[tp] = fabrica.crearEtiquetaPizzasPreparadas(i);
        if (es_estatico) {
            texto_servidas[tp] = fabrica.crearEtiquetaPizzasServidas(i);
        }
        i++;
    }
};

/* Actualiza texto_servidas */
void EtiquetasContadores::_actualizar_pedido_estatico(
    const modelo::PizzasAContadores &pizzas_a_contadores, //
    const modelo::Pedidos &pedidos                        //
) {
    assert(pedidos.size() == 1);
    const auto &pedido_unico = pedidos.at(0);
    for (auto &par : pizzas_a_contadores) {
        const auto &tp = par.first;
        const auto &contadores_tp = par.second;
        std::string servidas = presentador::crea_linea_completitud_pizza(
            tp, contadores_tp.servidas, pedido_unico.contenido.at(tp).objetivo
        );
        texto_servidas.at(tp).setString(servidas);
    }
}

/* Actualiza texto_pedidos */
void EtiquetasContadores::_actualizar_pedidos_dinamicos( //
    const modelo::Pedidos &pedidos
) {
    // Creamos las etiquetas con los textos
    const auto tamano_fuente = 22;
    texto_pedidos.clear();
    for (auto &pedido : pedidos) {
        const auto texto = presentador::pedido_to_string(pedido);
        const auto etiqueta = sf::Text(texto, font, tamano_fuente);
        texto_pedidos.push_back(etiqueta);
    }
    assert(texto_pedidos.size() == pedidos.size());

    // Les asignamos su posicion correcta
    float pos_x, pos_y;
    const auto separacion_vertical = medidas::SEPARACION_VERTICAL_ENTRE_PEDIDOS;

    // Calcula la posicion del primer pedido
    const auto pos_panel = obtener_posicion_panel(IndicePanel::PANEL_PEDIDOS);
    pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;

    for (auto &texto_pedido : texto_pedidos) {
        texto_pedido.setPosition(pos_x, pos_y);
        //  Calcula la posicion del siguiente pedido
        const auto g_bounds = texto_pedido.getGlobalBounds();
        pos_y = get_bottom(g_bounds) + separacion_vertical;
    }
}

void EtiquetasContadores::dibujar(sf::RenderWindow &ventana) const {
    for (auto &par : texto_preparadas) {
        auto &etiqueta = par.second;
        ventana.draw(etiqueta);
    }
    for (auto &par : texto_servidas) {
        auto &etiqueta = par.second;
        ventana.draw(etiqueta);
    }
    for (auto &etiqueta : texto_pedidos) {
        ventana.draw(etiqueta);
    }
}

void EtiquetasContadores::actualizar(
    const modelo::PizzasAContadores &pizzas_a_contadores, //
    const modelo::Pedidos &pedidos                        //
) {
    for (auto &par : pizzas_a_contadores) {
        const auto &tp = par.first;
        const auto &contadores_tp = par.second;
        auto &nombre_pizza = tipo_pizza_to_string.at(tp);
        std::string preparadas =
            nombre_pizza + ": " + std::to_string(contadores_tp.preparadas);
        texto_preparadas.at(tp).setString(preparadas);
    }
    if (es_estatico) {
        _actualizar_pedido_estatico(pizzas_a_contadores, pedidos);
    } else {
        _actualizar_pedidos_dinamicos(pedidos);
    }
}
