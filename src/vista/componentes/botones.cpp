#include "botones.h"
#include "varios.h"
#include <cassert>

/*
 * Crea un grupo de botones en un contenedor.
 */
std::vector<BotonConTexto> _crear_botones( //
    const std::vector<BotonDataConFont> &datos_botones,
    const sf::FloatRect &contenedor
) {
    // Crea los botones
    std::vector<BotonConTexto> botones;
    for (auto &dato : datos_botones) {
        botones.emplace_back(dato);
        botones.back().establecer_contenedor(contenedor);
    }
    return botones;
}

/*
 * Alinea una hilera de botones a la derecha desde una posicion inicial.
 * Los botones se posicionan de derecha a izquierda basandose en la
 * separacion especificada. Esta funcion modificara la posicion de los objetos
 * BotonConTexto a los que se apunta dentro del vector. El vector en si y los
 * punteros que contiene no se modificaran (no se anadiran ni eliminaran
 * botones).
 *
 * Parametros:
 *   - botones: vector de punteros a los objetos BotonConTexto que seran
 * alineados.
 *   - posicion_inicial: posicion del primer boton en la hilera.
 *   - separacion: espacio horizontal entre los botones.
 */
void _alinear_botones_derecha(
    const std::vector<BotonConTexto *> &botones, //
    const sf::Vector2f &posicion_inicial,        //
    int separacion                               //
) {
    int next_pos_x = posicion_inicial.x;
    for (auto &boton : botones) {
        const auto posicion = sf::Vector2f(next_pos_x, posicion_inicial.y);
        boton->establecer_posicion(posicion, Align::Right);
        const auto anterior_izquierda = boton->get_rect().left;
        next_pos_x = anterior_izquierda - separacion;
    }
}

/*
 * Crea una hilera de botones alienados a la derecha. El orden en el que se
 * reciben los datos y se anaden al vector de botones es de derecha a izquierda.
 */
std::vector<BotonConTexto> crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,               //
    const std::vector<BotonDataConFont> &datos_botones, //
    const sf::FloatRect &contenedor,                    //
    int separacion                                      //
) {
    auto botones = _crear_botones(datos_botones, contenedor);
    std::vector<BotonConTexto *> botones_ptr;
    for (auto &boton : botones) {
        botones_ptr.push_back(&boton);
    }
    _alinear_botones_derecha(botones_ptr, posicion_inicial, separacion);
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

/*
 * Coloca una serie de botones en vertical desde una posicion inicial.
 * Los botones se posicionaran de arriba a abajo basandose en la
 * diferencia (no separacion) especificada. Esta funcion modificara la posicion
 * de los objetos BotonConTexto a los que se apunta dentro del vector. El vector
 * en si y los punteros que contiene no se modificaran (no se anadiran ni
 * eliminaran botones).
 *
 * Parametros:
 *   - botones: vector de punteros a los objetos BotonConTexto que seran
 * posiciconados.
 *   - posicion_inicial: posicion del primer boton de la serie.
 *   - diferencia: diferencia vertical entre la posicion de inicio de un boton y
 *     la del siguiente.
 */
void colocar_botones_en_vertical(
    const std::vector<BotonConTexto *> &botones, //
    const sf::Vector2f &pos_inicial,             //
    float diferencia                             //
) {
    size_t i = 0;
    for (auto &boton : botones) {
        const auto posicion = _mover_vertical(pos_inicial, (diferencia * i++));
        boton->establecer_posicion(posicion);
    }
}
