#include "actualizar_iu.h"
#include "vista/vista_data.h"
#include <cassert>

/*
 * Actualiza el interfaz gráfico
 */
void actualizarIU(                             //
    sf::RenderWindow &ventana,                 //
    Botones &botones,                          //
    PanelesCompletos &paneles_completos,       //
    EtiquetasContadores &etiquetas_contadores, //
    EtiquetasInfo &etiquetas_info,             //
    Estado &estado,                            //
    Grid &grid,                                //
    sf::Font font                              //
) {

    // Actualiza el estado de los botones
    for (auto tp : tipos_de_pizza) {
        auto &boton_despachar = botones.despachar[tp];
        if (estado.contadores[tp].preparadas == 0) {
            boton_despachar.desactivar();
        } else {
            boton_despachar.activar();
        }
    }

    int total_en_preparacion = estado.encargadas.size();
    assert(total_en_preparacion <= MAXIMO_PIZZAS_EN_PREPARACION);

    for (auto &tp : tipos_de_pizza) {
        auto &boton_encargar = botones.encargar[tp];
        // Desactivar los botones si se alcanzó el máximo en preparación
        if (total_en_preparacion == MAXIMO_PIZZAS_EN_PREPARACION) {
            boton_encargar.desactivar();
            continue;
        } else {
            boton_encargar.activar();
        }
        // Desactivar los botones que harían sobrepasar los objetivos
        auto contadores = estado.contadores[tp];
        int potenciales = contadores.preparadas + contadores.servidas +
                          encargadas_del_tipo(estado.encargadas, tp);
        if (potenciales < contadores.objetivo) {
            boton_encargar.activar();
        } else {
            boton_encargar.desactivar();
        }
    }

    // Limpia la ventana y empieza a pintar los componentes visuales
    ventana.clear(colores::COLOR_FONDO);
    if (DRAW_GRID)
        draw_grid(ventana, grid, GRID_SIZE, GRID_TONE);

    // Paneles
    if ( //
        estado.fase_actual == Activa ||
        estado.fase_actual == EsperaAntesDeResultado
    ) {
        std::vector<PorcentajeConTipoPizza> porcentajes;
        poblar_porcentajes_de_preparacion(estado.encargadas, porcentajes);
        paneles_completos.dibujar(ventana, porcentajes, font);
    }

    // Textos
    switch (estado.fase_actual) {
        case MostrandoInstrucciones:
            ventana.draw(etiquetas_info.instrucciones);
            break;
        case Activa:
        case EsperaAntesDeResultado:
            etiquetas_contadores.actualizar(estado.contadores);
            etiquetas_contadores.dibujar(ventana);
            break;

        default:
            assert(estado.fase_actual == MostrandoResultado);
            ventana.draw(etiquetas_info.resultado);
            break;
    }

    botones.dibujar(ventana);

    ventana.display();
}
