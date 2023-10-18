#include "fabrica_botones.h"
#include "varios.h"
#include <cassert>

/*
 * Crea una hilera de botones.
 */
std::vector<BotonConTexto> crear_botones(
    const std::vector<BotonData> &datos_botones, //
    const sf::Font &font
) {
    // Crea los botones
    std::vector<BotonConTexto> botones;
    for (auto &dato : datos_botones) {
        botones.emplace_back(dato, font);
    }
    return botones;
}

/*
 * Alinea una hilera de botones a la derecha. El orden en el que se
 * reciben los datos y se anaden al vector de botones es de derecha a izquierda.
 */
void alinear_botones_derecha(
    std::vector<BotonConTexto *> botones,
    const sf::Vector2f &posicion_inicial, //
    int separacion
) {
    // Posiciona los botones
    int next_pos_x = posicion_inicial.x;
    for (auto &boton : botones) {
        const auto posicion = sf::Vector2f(next_pos_x, posicion_inicial.y);
        boton->establecerPosicion(posicion, Align::Right);
        const auto anterior_izquierda = boton->getGlobalBounds().left;
        next_pos_x = anterior_izquierda - separacion;
    }
}

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
    auto botones = crear_botones(datos_botones, font);
    std::vector<BotonConTexto *> vect_ptr;
    for (auto &boton : botones) {
        vect_ptr.push_back(&boton);
    }
    alinear_botones_derecha(vect_ptr, posicion_inicial, separacion);
    return botones;
}
