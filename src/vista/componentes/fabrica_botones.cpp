#include "fabrica_botones.h"
#include "varios.h"
#include <cassert>

/*
 * Crea una hilera de botones alienados a la derecha. El orden en el que se
 * reciben los datos y se anaden al vector de botones es de derecha a izquierda.
 */
std::vector<BotonConTexto> crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,        //
    const std::vector<BotonData> &datos_botones, //
    const sf::Font &font,                        //
    int separacion
) {
    std::vector<BotonConTexto> botones;
    int next_pos_x = posicion_inicial.x;
    for (auto &dato : datos_botones) {
        const auto posicion = sf::Vector2f(next_pos_x, posicion_inicial.y);
        botones.push_back( //
            BotonConTexto(dato, posicion, font, Align::Right)
        );
        const auto anterior_izquierda = botones.back().getGlobalBounds().left;
        next_pos_x = anterior_izquierda - separacion;
    }
    return botones;
}
