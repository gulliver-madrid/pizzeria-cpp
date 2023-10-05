#include "etiquetas.h"
#include "../templates.h"
#include "../textos.h"
#include "../vista/cadenas.h"
#include "componentes.h"
#include "vista_basics.h"

#define TAMANO_FUENTE_INFO 36
#define TAMANO_FUENTE_RESULTADO 48

namespace medidas {
    constexpr int TAMANO_FUENTE_TITULO_PANELES = 36;
    constexpr int TAMANO_FUENTE_ETIQUETAS = 24;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS = 50;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_SERVIDAS = 50;
    const sf::Vector2f POSICION_INSTRUCCIONES_O_RESULTADO = {200, 200};
} // namespace medidas

sf::Vector2f
get_posicion_etiqueta_titulo_panel(const sf::Vector2f &posicion_panel) {
    int pos_x = posicion_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y = posicion_panel.y + medidas::FILA_TITULOS_PANELES;
    return sf::Vector2f(pos_x, pos_y);
}

/* Usando posicion_panel */
sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, const sf::Vector2f &posicion_panel,
    const std::string &texto
) {
    auto tamano_fuente = medidas::TAMANO_FUENTE_TITULO_PANELES;
    auto posicion = get_posicion_etiqueta_titulo_panel(posicion_panel);
    auto etiqueta =
        crearEtiqueta(tamano_fuente, font, sf::Color::Green, posicion);
    etiqueta.setString(interpolar_unicode(texto));
    return etiqueta;
}

sf::Vector2f obtener_posicion_etiqueta_contador_pizzas(
    size_t indice_etiqueta, IndicePanel indice_panel,
    int desplazamiento_vertical
) {
    const auto pos_panel = obtener_posicion_panel(indice_panel);
    const auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    const auto pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL +
                       desplazamiento_vertical * indice_etiqueta;
    return sf::Vector2f(pos_x, pos_y);
}

/* Crea una etiqueta para un contador (dependiendo del panel tendrá uno u otro
 * significado)*/
sf::Text crearEtiquetaContadorPizzas(
    IndicePanel indice_panel,    //
    size_t indice_etiqueta,      //
    int desplazamiento_vertical, //
    const sf::Font &font         //
) {
    const auto posicion = obtener_posicion_etiqueta_contador_pizzas(
        indice_etiqueta, indice_panel, desplazamiento_vertical
    );
    const int tamano = medidas::TAMANO_FUENTE_ETIQUETAS;
    const auto color = sf::Color::White;
    const auto fuente = FuenteTexto{tamano, color, font};
    return crearEtiqueta(fuente, posicion);
}

sf::Text
crearEtiquetaPizzasPreparadas(const sf::Font &font, size_t indice_etiqueta) {
    return crearEtiquetaContadorPizzas(
        IndicePanel::PANEL_PREPARADAS,                                //
        indice_etiqueta,                                              //
        medidas::DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS, //
        font                                                          //
    );
}

sf::Text
crearEtiquetaPizzasServidas(const sf::Font &font, size_t indice_etiqueta) {
    return crearEtiquetaContadorPizzas(
        IndicePanel::PANEL_PEDIDOS,                                 //
        indice_etiqueta,                                            //
        medidas::DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_SERVIDAS, //
        font
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

std::string
crea_linea_completitud_pizza(const TipoPizza &tp, int parte, int todo) {
    const auto nombre_pizza = tipo_pizza_to_string.at(tp);
    std::string s = (           //
        nombre_pizza + ": " +   //
        std::to_string(parte) + //
        std::string("/") +      //
        std::to_string(todo)    //
    );
    return s;
}

/* Crea una string representando un pedido. Una línea por tipo de pizza, con el
 * formato TipoPizza: n/m
 */
std::string pedido_to_string(const Pedido &pedido) {
    std::string s;
    for (auto &par : pedido.contenido) {
        s.append(
            crea_linea_completitud_pizza(
                par.first, par.second.servido, par.second.objetivo
            ) +
            "\n"
        );
    }
    return s;
}

void EtiquetasContadores::actualizar(
    const PizzasAContadores &pizzas_a_contadores, //
    const Pedidos &pedidos,                       //
    bool es_estatico
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

float get_bottom(const sf::FloatRect &rect) { //
    return rect.top + rect.height;
}

void EtiquetasContadores::_actualizar_pedido_estatico(
    const PizzasAContadores &pizzas_a_contadores, //
    const Pedidos &pedidos                        //
) {
    assert(pedidos.size() == 1);
    const auto &pedido_unico = pedidos.at(0);
    for (auto &par : pizzas_a_contadores) {
        const auto &tp = par.first;
        const auto &contadores_tp = par.second;
        std::string servidas = crea_linea_completitud_pizza(
            tp, contadores_tp.servidas, pedido_unico.contenido.at(tp).objetivo
        );
        texto_servidas.at(tp).setString(servidas);
    }
}

void EtiquetasContadores::_actualizar_pedidos_dinamicos( //
    const Pedidos &pedidos
) {
    // Creamos las etiquetas con los textos
    const auto tamano_fuente = 22;
    texto_pedidos.clear();
    for (auto &pedido : pedidos) {
        const auto texto = pedido_to_string(pedido);
        const auto etiqueta = sf::Text(texto, font, tamano_fuente);
        texto_pedidos.push_back(etiqueta);
    }
    assert(texto_pedidos.size() == pedidos.size());

    // Les asignamos su posicion correcta
    float pos_x, pos_y;
    const auto separacion_vertical = 0;

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

sf::Text generar_etiqueta_instrucciones(
    const sf::Font &font,                       //
    const std::string &plantilla_instrucciones, //
    int num_nivel,                              //
    int objetivo
) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_INFO, font, colores::COLOR_TEXTO_INSTRUCCIONES,
        medidas::POSICION_INSTRUCCIONES_O_RESULTADO
    );
    etiqueta.setString(
        construir_instrucciones(plantilla_instrucciones, num_nivel, objetivo)
    );
    return etiqueta;
}

sf::Text generar_etiqueta_resultado(const sf::Font &font) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_RESULTADO, font, colores::COLOR_TEXTO_RESULTADO,
        medidas::POSICION_INSTRUCCIONES_O_RESULTADO
    );
    etiqueta.setString(construir_resultado());
    return etiqueta;
}

void EtiquetasGenerales::setup(
    const std::string &instr,                     //
    int num_nivel,                                //
    const std::vector<TipoPizza> &tp_disponibles, //
    bool es_estatico,                             //
    int total_objetivos
) {
    const auto instrucciones =
        generar_etiqueta_instrucciones(font, instr, num_nivel, total_objetivos);
    const auto resultado = generar_etiqueta_resultado(font);

    info = {instrucciones, resultado};
    contadores.setup(tp_disponibles, es_estatico);
}
