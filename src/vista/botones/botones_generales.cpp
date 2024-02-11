#include "botones_generales.h"
#include "../basicos_vista.h"
#include "../componentes/botones.h"

using std::vector;

namespace {

    const vector<BotonData> datos_botones_generales = {
        {"Salir", sf::Color::Red},             //
        {"Reiniciar", sf::Color(255, 120, 0)}, //
        {"Alternar Grid", sf::Color::Blue}     //
    };

    sf::Vector2f _obtener_pos_dcha_botones_generales() {
        const sf::Vector2f pos_ultimo_panel =
            basicos_vista::obtener_posicion_panel( //
                IndicePanel::PANEL_PEDIDOS
            );
        return sf::Vector2f(
            pos_ultimo_panel.x + medidas::ANCHO_PANEL,
            medidas::FILA_BOTONES_GENERALES
        );
    }

} // namespace

BotonesGenerales crear_botones_generales() {
    const auto pos_derecha = _obtener_pos_dcha_botones_generales();
    auto botones = crear_botones_alineados_derecha(
        pos_derecha,                                           //
        datos_botones_generales,                               //
        sf::FloatRect(),                                       //
        medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES //
    );

    assert(botones.size() == 3);
    return {
        botones.at(2),
        botones.at(1),
        botones.at(0),
    };
}

///////////////////////////////////////////
// BotonesGenerales
//////////////////////////////////////////

Botones BotonesGenerales::obtener_todos() const {
    return {alternar_grid, reiniciar, salir};
}
void BotonesGenerales::alinear() {
    // TODO: eliminar duplicacion con otro metodo
    const auto pos_derecha = _obtener_pos_dcha_botones_generales();
    const auto separacion =
        medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES;
    alinear_botones_derecha(
        {alternar_grid, reiniciar, salir}, pos_derecha, separacion
    );
}
