#include "botones.h"
#include "../posiciones.h"
#include "crear_etiqueta.h"
#include <cassert>

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
void alinear_botones_derecha(
    const Botones &botones,                   //
    const PosicionRelativa &posicion_inicial, //
    float separacion                          //
) {
    auto next_pos_x = posicion_inicial.valor.x;
    for (auto &boton : botones) {
        const auto posicion =
            PosicionRelativa{sf::Vector2f(next_pos_x, posicion_inicial.valor.y)
            };
        boton->establecer_posicion_relativa(posicion, Align::Right);
        const auto anterior_izquierda = boton->get_rect().left;
        next_pos_x = anterior_izquierda - separacion;
    }
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
    const std::vector<std::shared_ptr<BotonConTexto>> &botones, //
    const PosicionRelativa &pos_inicial,                        //
    float diferencia,                                           //
    const sf::FloatRect &contenedor                             //
) {
    size_t i = 0;
    for (auto &boton : botones) {
        const auto posicion = PosicionRelativa{
            _mover_vertical(pos_inicial.valor, (diferencia * i++))
        };
        boton->establecer_contenedor(contenedor);
        boton->establecer_posicion_relativa(posicion);
    }
}
