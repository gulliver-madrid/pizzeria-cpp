#include "fabrica_etiquetas_contadores.h"
#include "componentes/varios.h"
#include "vista_basics.h"

namespace medidas {
    constexpr int TAMANO_FUENTE_ETIQUETAS = 24;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS = 50;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_SERVIDAS = 50;
} // namespace medidas

/*
 * Obtiene la posicion de una etiqueta para un contador
 */
sf::Vector2f
FabricaEtiquetasContadores::_obtener_posicion_etiqueta_contador_pizzas(
    const sf::Vector2f pos_panel, size_t indice_etiqueta,
    int desplazamiento_vertical
) {
    const auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    const auto pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL +
                       desplazamiento_vertical * indice_etiqueta;
    return sf::Vector2f(pos_x, pos_y);
}

/*
 * Crea una etiqueta para un contador (dependiendo del panel tendrá uno u
 * otro significado)
 */
sf::Text FabricaEtiquetasContadores::_crearEtiquetaContadorPizzas(
    sf::Vector2f posicion_panel, //
    size_t indice_etiqueta,      //
    int desplazamiento_vertical  //
) {
    const auto posicion = _obtener_posicion_etiqueta_contador_pizzas(
        posicion_panel, indice_etiqueta, desplazamiento_vertical
    );
    const int tamano = medidas::TAMANO_FUENTE_ETIQUETAS;
    const auto color = sf::Color::White;
    const auto estilo_texto = EstiloTexto{tamano, color, font};
    return crearEtiqueta(estilo_texto, posicion);
}

/*
 * Crea una etiqueta de pizzas preparadas
 */
sf::Text
FabricaEtiquetasContadores::crearEtiquetaPizzasPreparadas(size_t indice_etiqueta
) {
    return _crearEtiquetaContadorPizzas(
        obtener_posicion_panel(IndicePanel::PANEL_PREPARADAS),       //
        indice_etiqueta,                                             //
        medidas::DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS //
    );
}

/*
 * Crea una etiqueta de pizzas servidas
 */
sf::Text
FabricaEtiquetasContadores::crearEtiquetaPizzasServidas(size_t indice_etiqueta
) {
    return _crearEtiquetaContadorPizzas(
        obtener_posicion_panel(IndicePanel::PANEL_PEDIDOS),        //
        indice_etiqueta,                                           //
        medidas::DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_SERVIDAS //
    );
}
