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
void Vista::actualizarIU(      //
    sf::RenderWindow &ventana, //
    const Estado &estado,      //
    sf::Font font              //
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

/* Activa o desactiva cada botón despachar dependiendo de si hay pizzas
 * preparadas de ese tipo */
void activar_botones_despachar_si_hay_preparadas(
    std::map<TipoPizza, BotonConTexto> &botones_despachar,
    const PizzasAContadores &contadores
) {
    for (auto &par : contadores) {
        auto &tp = par.first;
        auto &contador = par.second;
        auto &boton_despachar = botones_despachar[tp];
        boton_despachar.activar_cuando(contador.preparadas > 0);
    }
}

/* Solo se ejecutará en modo estático */
void desactivar_botones_encargar_si_se_sobrepasan_objetivos(
    std::map<TipoPizza, BotonConTexto> &botones_encargar,
    const PizzasAContadores &contadores, const Encargos &encargos,
    const Pedido &pedido
) {
    for (auto &par : contadores) {
        auto &tp = par.first;
        auto &boton_encargar = botones_encargar.at(tp);
        if (!boton_encargar.activo) {
            continue;
        }
        auto &contadores_tp = par.second;
        int potenciales = contadores_tp.preparadas + contadores_tp.servidas +
                          encargos.del_tipo(tp);
        auto contador_estatico_tp = pedido.contenido.at(tp);
        if (potenciales >= contador_estatico_tp.objetivo) {
            boton_encargar.desactivar();
        }
    }
}

void actualizar_estado_botones(Botones &botones, const Estado &estado) {
    if (!estado.control_pizzas.es_estatico) {
        assert(false && "No implementado");
        // TODO: implementar
        return;
    }
    const PizzasAContadores &contadores = estado.control_pizzas.contadores;
    activar_botones_despachar_si_hay_preparadas(botones.despachar, contadores);

    int total_en_preparacion = estado.encargos.total();
    assert(total_en_preparacion <= MAXIMO_PIZZAS_EN_PREPARACION);
    const bool se_pueden_preparar_mas =
        total_en_preparacion < MAXIMO_PIZZAS_EN_PREPARACION;

    for (auto &par : botones.encargar) {
        auto &boton_encargar = par.second;
        boton_encargar.activar_cuando(se_pueden_preparar_mas);
    }
    if (se_pueden_preparar_mas && estado.control_pizzas.es_estatico) {
        assert(estado.control_pizzas.pedidos.size() == 1);
        // Desactivar los botones que harían sobrepasar los objetivos
        auto &pedido = estado.control_pizzas.pedidos[0];
        desactivar_botones_encargar_si_se_sobrepasan_objetivos(
            botones.encargar, contadores, estado.encargos, pedido
        );
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
