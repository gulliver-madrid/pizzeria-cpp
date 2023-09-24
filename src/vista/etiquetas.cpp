#include "etiquetas.h"
#include "../cadenas.h"
#include "../textos.h"
#include "componentes.h"
#include "vista_basics.h"

#define TAMANO_FUENTE_INFO 36
#define TAMANO_FUENTE_RESULTADO 48

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

// Crea la etiqueta de texto que mostrará el contador
sf::Text crearEtiquetaContador(const sf::Font &font, int indice_etiqueta) {
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    etiqueta.setPosition(
        obtener_posicion_x_panel(PANEL_PEDIDOS) + medidas::MARGEN_IZQ_ETIQUETAS,
        medidas::FILA_CONTENIDO_PANEL + 50 * indice_etiqueta
    );
    return etiqueta;
}
sf::Text
crearEtiquetaPizzasPreparadas(const sf::Font &font, int indice_etiqueta) {
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    auto pos_x = obtener_posicion_x_panel(PANEL_PREPARADAS) +
                 medidas::MARGEN_IZQ_ETIQUETAS;
    etiqueta.setPosition(
        pos_x, medidas::FILA_CONTENIDO_PANEL + 50 * indice_etiqueta
    );
    return etiqueta;
}

void EtiquetasContadores::setup(sf::Font &font) {
    int i = 0;
    for (auto tp : tipos_de_pizza) {
        texto_servidas[tp] = crearEtiquetaContador(font, i);
        texto_preparadas[tp] = crearEtiquetaPizzasPreparadas(font, i);
        i++;
    }
};

void EtiquetasContadores::dibujar(sf::RenderWindow &ventana) {
    for (auto &tp : tipos_de_pizza) {
        ventana.draw(texto_servidas[tp]);
        ventana.draw(texto_preparadas[tp]);
    }
}

sf::Text generar_etiqueta_instrucciones(
    sf::Font &font, std::string plantilla_instrucciones, int objetivo
) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_INFO, font, colores::COLOR_TEXTO_INSTRUCCIONES
    );
    etiqueta.setString(
        construir_instrucciones(plantilla_instrucciones, objetivo)
    );
    etiqueta.setPosition(200, 200);
    return etiqueta;
}

sf::Text generar_etiqueta_resultado(sf::Font &font) {
    auto etiqueta = crearEtiqueta(
        TAMANO_FUENTE_RESULTADO, font, colores::COLOR_TEXTO_RESULTADO
    );
    etiqueta.setString(construir_resultado());
    etiqueta.setPosition(200, 200);
    return etiqueta;
}
