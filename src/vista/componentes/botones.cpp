#include "botones.h"
#include "crear_etiqueta.h"
#include <cassert>

/*
 * Crea un grupo de botones en un contenedor.
 */
Botones _crear_botones( //
    const std::vector<BotonData> &datos_botones, const sf::FloatRect &contenedor
) {
    // Crea los botones
    Botones botones;
    for (auto &dato : datos_botones) {
        botones.push_back(std::make_shared<BotonConTexto>(dato));
        botones.back()->establecer_contenedor(contenedor);
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
void alinear_botones_derecha(
    const Botones &botones,               //
    const sf::Vector2f &posicion_inicial, //
    float separacion                      //
) {
    auto next_pos_x = posicion_inicial.x;
    for (auto &boton : botones) {
        const auto posicion = sf::Vector2f(next_pos_x, posicion_inicial.y);
        boton->establecer_posicion_relativa(posicion, Align::Right);
        const auto anterior_izquierda = boton->get_rect().left;
        next_pos_x = anterior_izquierda - separacion;
    }
}

/*
 * Crea una hilera de botones alienados a la derecha. El orden en el que se
 * reciben los datos y se anaden al vector de botones es de derecha a izquierda.
 */
Botones crear_botones_alineados_derecha(
    const sf::Vector2f &posicion_inicial,        //
    const std::vector<BotonData> &datos_botones, //
    const sf::FloatRect &contenedor,             //
    float separacion                             //
) {
    auto botones = _crear_botones(datos_botones, contenedor);
    alinear_botones_derecha(botones, posicion_inicial, separacion);
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
    const std::vector<std::shared_ptr<BotonConTexto>> &botones, //
    const sf::Vector2f &pos_inicial,                            //
    float diferencia,                                           //
    const sf::FloatRect &contenedor                             //
) {
    size_t i = 0;
    for (auto &boton : botones) {
        const auto posicion = _mover_vertical(pos_inicial, (diferencia * i++));
        boton->establecer_contenedor(contenedor);
        boton->establecer_posicion_relativa(posicion);
    }
}
