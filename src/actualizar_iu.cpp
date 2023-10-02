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
    const Estado &estado,                //
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
    const Estado &estado,                //
    Grid &grid,                          //
    sf::Font font                        //
) {
    // std::cout << "\nActualizando IU" << std::endl;

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
    if (!estado.control_pizzas.es_estatico) {
        assert(false && "No implementado");
        // TODO: implementar
        return;
    }
    const PizzasAContadores &contadores = estado.control_pizzas.contadores;
    for (auto &par : contadores) {
        auto tp = par.first;
        auto &boton_despachar = botones.despachar[tp];
        if (contadores.at(tp).preparadas == 0) {
            boton_despachar.desactivar();
        } else {
            boton_despachar.activar();
        }
    }

    int total_en_preparacion = estado.encargos.total();
    assert(total_en_preparacion <= MAXIMO_PIZZAS_EN_PREPARACION);

    for (auto &par : contadores) {
        auto &tp = par.first;
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

        if (estado.control_pizzas.es_estatico) {
            auto &pedido = estado.control_pizzas.pedidos[0];
            auto contador_estatico_tp = pedido.contenido.at(tp);
            if (potenciales < contador_estatico_tp.objetivo) {
                boton_encargar.activar();
            } else {
                boton_encargar.desactivar();
            }
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

            if (!estado.control_pizzas.es_estatico) {
                assert(false && "No implementado");
                // TODO: implementar
                return;
            }
            {
                const PizzasAContadores &contadores =
                    estado.control_pizzas.contadores;
                // std::cout << "En actualizar iu" << std::endl;
                // debug_contadores(contadores);
                const auto &pedido = estado.control_pizzas.pedidos[0];
                std::optional<Pedido> pedido_opt = pedido;
                etiquetas.contadores.actualizar(contadores, pedido_opt);
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
    const Estado &estado,                //
    sf::Font font                        //
) {
    EstadoPreparacionPizzas preparacion(estado.encargos);
    paneles_completos.dibujar(ventana, preparacion, font);
}
