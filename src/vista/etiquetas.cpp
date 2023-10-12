#include "etiquetas.h"
#include "../templates.h"
#include "../textos.h"
#include "../vista/cadenas.h"
#include "componentes.h"
#include "etiquetas_contadores.h"
#include "vista_basics.h"

#define TAMANO_FUENTE_INFO 36
#define TAMANO_FUENTE_RESULTADO 48

namespace medidas {
    constexpr int TAMANO_FUENTE_TITULO_PANELES = 36;
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

sf::Text generar_etiqueta_instrucciones(
    const sf::Font &font,         //
    const std::string &plantilla, //
    NumNivel num_nivel,           //
    int objetivo
) {
    const auto color = colores::COLOR_TEXTO_INSTRUCCIONES;
    const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
    FuenteTexto fuente_texto{TAMANO_FUENTE_INFO, color, font};
    auto etiqueta = crearEtiqueta(fuente_texto, posicion);
    const auto texto = construir_instrucciones(plantilla, num_nivel, objetivo);
    etiqueta.setString(texto);
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

EtiquetasGenerales::EtiquetasGenerales(bool es_estatico, const sf::Font &font)
    : font(font) {
    contadores = std::make_unique<EtiquetasContadores>(es_estatico, font);
}

EtiquetasGenerales::~EtiquetasGenerales() = default;

void EtiquetasGenerales::setup(
    const std::string &instr,                     //
    NumNivel num_nivel,                           //
    const std::vector<TipoPizza> &tp_disponibles, //
    int total_objetivos                           //
) {
    const auto instrucciones =
        generar_etiqueta_instrucciones(font, instr, num_nivel, total_objetivos);
    const auto resultado = generar_etiqueta_resultado(font);
    info = {instrucciones, resultado};
    contadores->setup(tp_disponibles);
}

void EtiquetasGenerales::actualizar_y_dibujar_contadores(
    const PizzasAContadores &pizzas_a_contadores, //
    const Pedidos &pedidos,                       //
    sf::RenderWindow &ventana                     //
) {
    contadores->actualizar(pizzas_a_contadores, pedidos);
    contadores->dibujar(ventana);
}
