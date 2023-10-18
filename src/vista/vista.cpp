#include "vista.h"
#include "../estado_nivel.h"
#include "basicos_vista.h"
#include "grid.h"
#include "vista_data.h"
#include <cassert>

void actualizar_estado_botones(BotonesApp &botones, const Estado &estado);
void actualizar_etiquetas(
    sf::RenderWindow &ventana,               //
    EtiquetasGenerales &etiquetas_generales, //
    const Estado &estado                     //
);

void Vista::setup(
    const std::string &instrucciones,          //
    const NumNivel &num_nivel,                 //
    const std::optional<int> objetivo_estatico //
) {
    etiquetas.setup(
        instrucciones,    //
        num_nivel,        //
        tp_disponibles,   //
        objetivo_estatico //
    );
    // Mostrar botones iniciales
    botones.generales.alternar_grid.visible = MODO_DESARROLLO;
    botones.generales.reiniciar.visible = true;
    botones.generales.salir.visible = true;
    botones.empezar.visible = true;
}

/*
 * Actualiza el interfaz gráfico
 */
void Vista::actualizarIU(      //
    sf::RenderWindow &ventana, //
    const Estado &estado       //
) {
    // std::cout << "\nActualizando IU" << std::endl;

    actualizar_estado_botones(botones, estado);

    // Limpia la ventana y empieza a pintar los componentes visuales
    ventana.clear(colores::COLOR_FONDO);
    if (estado.mostrando_grid)
        grid.draw(ventana, GRID_SIZE, GRID_TONE);

    if ( //
        estado.fase_actual == FaseNivel::Activa ||
        estado.fase_actual == FaseNivel::EsperaAntesDeResultado
    ) {
        actualizar_paneles(ventana, paneles_completos, estado.encargos);
    }

    actualizar_etiquetas(ventana, etiquetas, estado);

    botones.dibujar(ventana);

    ventana.display();
}

void Vista::procesa_cambio_de_fase(FaseNivel nueva_fase) {
    switch (nueva_fase) {
        case FaseNivel::Activa:
            botones.empezar.visible = false;
            botones.mostrar_botones_nivel(true);
            paneles_completos.visible = true;
            break;
        case FaseNivel::EsperaAntesDeResultado:
            botones.mostrar_botones_nivel(false);
            break;
    }
}

/*
 * Activa o desactiva cada botón despachar dependiendo de si hay pizzas
 * preparadas de ese tipo.
 */
void activar_botones_despachar_si_hay_preparadas(
    TipoPizzaToBoton &botones_despachar,
    const modelo::PizzasAContadores &contadores
) {
    for (auto &[tp, contadores_tp] : contadores) {
        auto &boton_despachar = botones_despachar.at(tp);
        boton_despachar.activacion_condicional(contadores_tp.preparadas > 0);
    }
}

/* Desactiva los botones encargar de cada tipo de pizza que ya tenga suficientes
 * unidades encargadas, preparadas y/o servidas.  Solo se ejecutará en modo
 * estático.
 */
void desactivar_botones_encargar_si_se_sobrepasan_objetivos(
    TipoPizzaToBoton &botones_encargar,          //
    const modelo::PizzasAContadores &contadores, //
    const Encargos &encargos,                    //
    const Pedido &pedido                         //
) {
    for (auto &[tp, contadores_tp] : contadores) {
        auto &boton_encargar = botones_encargar.at(tp);
        if (!boton_encargar.esta_activo()) {
            continue;
        }
        int potenciales = contadores_tp.preparadas + contadores_tp.servidas +
                          encargos.del_tipo(tp);
        auto contador_estatico_tp = pedido.contenido.at(tp);
        if (potenciales >= contador_estatico_tp.objetivo) {
            boton_encargar.desactivar();
        }
    }
}

/* Actualiza el estado de los botones en funcion de varios factores */
void actualizar_estado_botones(BotonesApp &botones, const Estado &estado) {
    const auto &control_pizzas = estado.control_pizzas;
    // Botones despachar
    const modelo::PizzasAContadores &contadores = control_pizzas.contadores;
    activar_botones_despachar_si_hay_preparadas(botones.despachar, contadores);

    // Botones encargar
    constexpr int maximo = modelo_info::MAXIMO_PIZZAS_EN_PREPARACION;
    const int en_preparacion = estado.encargos.total();
    assert(en_preparacion <= maximo);
    const bool se_pueden_preparar_mas = en_preparacion < maximo;

    for (auto &[_, boton] : botones.encargar) {
        boton.activacion_condicional(se_pueden_preparar_mas);
    }

    if (se_pueden_preparar_mas && control_pizzas.es_estatico.valor) {
        const auto &pedidos = control_pizzas.pedidos;
        assert(pedidos.size() == 1);
        const auto &pedido = pedidos[0];
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

    const modelo::PizzasAContadores &contadores =
        estado.control_pizzas.contadores;

    auto pedidos = estado.control_pizzas.pedidos;
    switch (estado.fase_actual) {
        case FaseNivel::MostrandoInstrucciones:
            etiquetas.dibujar_instrucciones(ventana);
            break;
        case FaseNivel::Activa:
        case FaseNivel::EsperaAntesDeResultado:
            etiquetas.actualizar_y_dibujar_contadores(
                contadores, pedidos, ventana
            );
            break;
        case FaseNivel::MostrandoResultado:
            etiquetas.dibujar_resultado(ventana);
            break;
        default:
            break;
    }
}

void Vista::actualizar_paneles(
    sf::RenderWindow &ventana,           //
    PanelesCompletos &paneles_completos, //
    const Encargos &encargos             //

) {
    EstadoPreparacionPizzas preparacion(encargos);
    paneles_completos.dibujar(ventana, preparacion, font);
}
