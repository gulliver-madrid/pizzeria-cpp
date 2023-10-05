#include "etiquetas.h"
#include "../templates.h"
#include "../textos.h"
#include "../vista/cadenas.h"
#include "componentes.h"
#include "vista_basics.h"

#define TAMANO_FUENTE_INFO 36
#define TAMANO_FUENTE_RESULTADO 48
#define POSICION_INSTRUCCIONES_O_RESULTADO 200, 200

namespace medidas {
    constexpr int TAMANO_FUENTE_TITULO_PANELES = 36;
    constexpr int TAMANO_FUENTE_ETIQUETAS = 24;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS = 50;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_SERVIDAS = 50;
} // namespace medidas

/* Usando posicion_panel */
sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, sf::Vector2i posicion_panel, const std::string &texto
) {
    sf::Text etiqueta = crearEtiqueta(
        medidas::TAMANO_FUENTE_TITULO_PANELES, font, sf::Color::White
    );
    int pos_x = posicion_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y = posicion_panel.y + medidas::FILA_TITULOS_PANELES;
    etiqueta.setPosition(pos_x, pos_y);
    etiqueta.setString(interpolar_unicode(texto));
    etiqueta.setFillColor(sf::Color::Green);
    return etiqueta;
}

sf::Text crearEtiquetaContadorPizzas(
    const sf::Font &font, int indice_etiqueta, IndicePanel indice_panel,
    int desplazamiento_vertical
) {
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    auto pos_panel = obtener_posicion_panel(indice_panel);
    auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    auto pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL +
                 desplazamiento_vertical * indice_etiqueta;
    etiqueta.setPosition(pos_x, pos_y);
    return etiqueta;
}

sf::Text
crearEtiquetaPizzasPreparadas(const sf::Font &font, int indice_etiqueta) {
    return crearEtiquetaContadorPizzas(
        font, indice_etiqueta, IndicePanel::PANEL_PREPARADAS,
        medidas::DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS
    );
}

sf::Text
crearEtiquetaPizzasServidas(const sf::Font &font, int indice_etiqueta) {
    return crearEtiquetaContadorPizzas(
        font, indice_etiqueta, IndicePanel::PANEL_PEDIDOS,
        medidas::DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_SERVIDAS
    );
}
void EtiquetasContadores::setup(
    const std::vector<TipoPizza> &tp_disponibles, bool es_estatico
) {
    int i = 0;
    for (auto &tp : tp_disponibles) {
        texto_preparadas[tp] = crearEtiquetaPizzasPreparadas(font, i);
        if (es_estatico) {
            texto_servidas[tp] = crearEtiquetaPizzasServidas(font, i);
        }
        i++;
    }
};

std::string pedido_to_string(const Pedido &pedido) {
    std::string s;
    for (auto &par : pedido.contenido) {
        s += tipo_pizza_to_string.at(par.first);
        s += ": ";
        s += std::to_string(par.second.servido);
        s += "/";
        s += std::to_string(par.second.objetivo);
        s += "\n";
    }
    return s;
}

void EtiquetasContadores::actualizar(
    const PizzasAContadores &pizzas_a_contadores, //
    const Pedidos &pedidos,                       //
    bool es_estatico
) {
    // std::cout << "\nEn EtiquetasContadores::actualizar() " << std::endl;
    for (auto &par : pizzas_a_contadores) {
        const auto &tp = par.first;
        const auto &contadores_tp = par.second;
        auto &nombre_pizza = tipo_pizza_to_string[tp];
        std::string preparadas =
            nombre_pizza + ": " + std::to_string(contadores_tp.preparadas);
        texto_preparadas[tp].setString(preparadas);
        if (es_estatico) {
            auto &pedido_unico = pedidos.at(0);
            std::string servidas = (                                   //
                nombre_pizza + ": " +                                  //
                std::to_string(contadores_tp.servidas) +               //
                std::string("/") +                                     //
                std::to_string(pedido_unico.contenido.at(tp).objetivo) //
            );
            texto_servidas[tp].setString(servidas);
        } else {
            auto separacion_vertical = 0;
            texto_pedidos.clear();
            auto pos_panel = obtener_posicion_panel(IndicePanel::PANEL_PEDIDOS);
            const auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
            auto pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
            for (auto &pedido : pedidos) {
                auto texto_pedido =
                    sf::Text(pedido_to_string(pedido), font, 22);
                texto_pedido.setPosition(sf::Vector2f(pos_x, pos_y));
                auto g_bounds = texto_pedido.getGlobalBounds();
                pos_y = g_bounds.top + g_bounds.height + separacion_vertical;
                texto_pedidos.push_back(texto_pedido);
            }
        }
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

sf::Text generar_etiqueta_instrucciones(
    const sf::Font &font,                       //
    const std::string &plantilla_instrucciones, //
    int num_nivel,                              //
    int objetivo
) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_INFO, font, colores::COLOR_TEXTO_INSTRUCCIONES
    );
    etiqueta.setString(
        construir_instrucciones(plantilla_instrucciones, num_nivel, objetivo)
    );
    etiqueta.setPosition(POSICION_INSTRUCCIONES_O_RESULTADO);
    return etiqueta;
}

sf::Text generar_etiqueta_resultado(const sf::Font &font) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_RESULTADO, font, colores::COLOR_TEXTO_RESULTADO
    );
    etiqueta.setString(construir_resultado());
    etiqueta.setPosition(POSICION_INSTRUCCIONES_O_RESULTADO);
    return etiqueta;
}

void EtiquetasGenerales::setup(
    const std::string &instr,                     //
    int num_nivel,                                //
    const std::vector<TipoPizza> &tp_disponibles, //
    bool es_estatico,                             //
    int total_objetivos
) {
    auto instrucciones =
        generar_etiqueta_instrucciones(font, instr, num_nivel, total_objetivos);
    auto resultado = generar_etiqueta_resultado(font);

    info = {instrucciones, resultado};
    contadores.setup(tp_disponibles, es_estatico);
}
