#include "actualizar_iu.h"
#include "estado_nivel.h"
#include "vista/grid.h"
#include "vista/vista_basics.h"
#include "vista/vista_data.h"
#include <cassert>

void actualizar_estado_botones(Botones &botones, const Estado &estado);
void actualizar_etiquetas(
    sf::RenderWindow &ventana,               //
    EtiquetasGenerales &etiquetas_generales, //
    const Estado &estado                     //
);
void actualizar_paneles(
    sf::RenderWindow &ventana,           //
    PanelesCompletos &paneles_completos, //
    Estado &estado,                      //
    sf::Font font                        //
);

/*
 * Actualiza el interfaz gráfico
 */
void actualizarIU(                       //
    sf::RenderWindow &ventana,           //
    Botones &botones,                    //
    PanelesCompletos &paneles_completos, //
    EtiquetasGenerales &etiquetas,       //
    Estado &estado,                      //
    Grid &grid,                          //
    sf::Font font                        //
) {
    actualizar_estado_botones(botones, estado);

    // Limpia la ventana y empieza a pintar los componentes visuales
    ventana.clear(colores::COLOR_FONDO);
    if (DRAW_GRID)
        draw_grid(ventana, grid, GRID_SIZE, GRID_TONE);

    if ( //
        estado.fase_actual == FaseNivel::Activa ||
        estado.fase_actual == FaseNivel::EsperaAntesDeResultado
    ) {
        actualizar_paneles(ventana, paneles_completos, estado, font);
    }

    actualizar_etiquetas(ventana, etiquetas, estado);

    botones.dibujar(ventana);

    ventana.display();
}

void actualizar_estado_botones(Botones &botones, const Estado &estado) {
    if (estado.control_pizzas->tipo == TipoSistemaPedidos::Dinamico) {
        // TODO: implementar
        return;
    }
    const PizzasAContadores &contadores =
        estado.control_pizzas->get_contadores_const();

    for (auto tp : tipos_de_pizza) {
        auto &boton_despachar = botones.despachar[tp];
        if (contadores.at(tp).preparadas == 0) {
            boton_despachar.desactivar();
        } else {
            boton_despachar.activar();
        }
    }

    int total_en_preparacion = estado.encargos.total();
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
        auto contadores_tp = contadores.at(tp);
        int potenciales = contadores_tp.preparadas + contadores_tp.servidas +
                          estado.encargos.del_tipo(tp);
        if (potenciales < contadores_tp.objetivo) {
            boton_encargar.activar();
        } else {
            boton_encargar.desactivar();
        }
    }
}

void actualizar_etiquetas(
    sf::RenderWindow &ventana,     //
    EtiquetasGenerales &etiquetas, //
    const Estado &estado           //
) {

    switch (estado.fase_actual) {
        case FaseNivel::MostrandoInstrucciones:
            ventana.draw(etiquetas.info.instrucciones);
            break;
        case FaseNivel::Activa:
        case FaseNivel::EsperaAntesDeResultado:

            if (estado.control_pizzas->tipo == TipoSistemaPedidos::Dinamico) {
                // TODO: implementar
                return;
            }
            {
                const PizzasAContadores &contadores =
                    estado.control_pizzas->get_contadores_const();
                etiquetas.contadores.actualizar(contadores);
                etiquetas.contadores.dibujar(ventana);
            }
            break;

        default:
            assert(estado.fase_actual == FaseNivel::MostrandoResultado);
            ventana.draw(etiquetas.info.resultado);
            break;
    }
}

void actualizar_paneles(
    sf::RenderWindow &ventana,           //
    PanelesCompletos &paneles_completos, //
    Estado &estado,                      //
    sf::Font font                        //
) {
    EstadoPreparacionPizzas preparacion(estado.encargos);
    paneles_completos.dibujar(ventana, preparacion, font);
}
