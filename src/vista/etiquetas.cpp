#include "etiquetas.h"
#include "../cadenas.h"
#include "../templates.h"
#include "../textos.h"
#include "componentes.h"
#include "vista_basics.h"

#define TAMANO_FUENTE_INFO 36
#define TAMANO_FUENTE_RESULTADO 48
#define POSICION_INSTRUCCIONES_O_RESULTADO 200, 200

sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, IndicePanel indice_panel, const std::string &texto
) {
    sf::Text etiqueta = crearEtiqueta(
        medidas::TAMANO_FUENTE_TITULO_PANELES, font, sf::Color::White
    );
    int pos_x =
        obtener_posicion_x_panel(indice_panel) + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y = medidas::FILA_TITULOS_PANELES;
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
    auto pos_x =
        obtener_posicion_x_panel(indice_panel) + medidas::MARGEN_IZQ_ETIQUETAS;
    auto pos_y = medidas::FILA_CONTENIDO_PANEL +
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

void EtiquetasContadores::setup(sf::Font &font) {
    int i = 0;
    for (auto tp : tipos_de_pizza) {
        texto_servidas[tp] = crearEtiquetaPizzasServidas(font, i);
        texto_preparadas[tp] = crearEtiquetaPizzasPreparadas(font, i);
        i++;
    }
};

void EtiquetasContadores::actualizar(
    const PizzasAContadores &pizzas_a_contadores
) {
    for (auto tp : tipos_de_pizza) {
        const auto &contadores = pizzas_a_contadores.at(tp);
        auto &nombre_pizza = tipo_pizza_to_string[tp];
        std::string preparadas =
            nombre_pizza + ": " + std::to_string(contadores.preparadas);
        std::string servidas = nombre_pizza + ": " +
                               std::to_string(contadores.servidas) + "/" +
                               std::to_string(contadores.objetivo);
        texto_preparadas[tp].setString(preparadas);
        texto_servidas[tp].setString(servidas);
    }
}

void EtiquetasContadores::dibujar(sf::RenderWindow &ventana) const {
    for (auto &tp : tipos_de_pizza) {
        ventana.draw(texto_servidas.at(tp));
        ventana.draw(texto_preparadas.at(tp));
    }
}

sf::Text generar_etiqueta_instrucciones(
    const sf::Font &font, const std::string &plantilla_instrucciones,
    int objetivo
) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_INFO, font, colores::COLOR_TEXTO_INSTRUCCIONES
    );
    etiqueta.setString(
        construir_instrucciones(plantilla_instrucciones, objetivo)
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
