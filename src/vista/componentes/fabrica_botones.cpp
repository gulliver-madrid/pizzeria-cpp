#include "fabrica_botones.h"
#include "varios.h"
#include <cassert>

/*
 * Crea una hilera de botones.
 */
std::vector<BotonConTexto> _crear_botones(
    const std::vector<BotonData> &datos_botones, //
    const sf::Font &font                         //
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
void _alinear_botones_derecha(
    const std::vector<BotonConTexto *> &botones, //
    const sf::Vector2f &posicion_inicial,        //
    int separacion                               //
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
    int separacion                               //
) {
    auto botones = _crear_botones(datos_botones, font);
    std::vector<BotonConTexto *> vect_ptr;
    for (auto &boton : botones) {
        vect_ptr.push_back(&boton);
    }
    _alinear_botones_derecha(vect_ptr, posicion_inicial, separacion);
    return botones;
}

/*
 * Devuelve un nuevo Vector2f como consecuencia de
 * desplazar verticalmente el proporcionado
 */
sf::Vector2f _mover_vertical( //
    const sf::Vector2f &inicial, float desplazamiento
) {
    return inicial + sf::Vector2f(0, desplazamiento);
}

void colocar_botones_en_vertical(
    const std::vector<BotonConTexto *> &botones, //
    const sf::Vector2f &pos_inicial,             //
    float diferencia                             //
) {
    size_t i = 0;
    for (auto &boton : botones) {
        const auto posicion = _mover_vertical(pos_inicial, (diferencia * i++));
        boton->establecerPosicion(posicion);
    }
}
