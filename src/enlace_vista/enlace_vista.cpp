#include "enlace_vista.h"
#include "../fase_nivel.h"
#include "../shared/log_init.h"
#include "../templates/helpers.h"
#include "../vista/paneles.h"
#include "presentador.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include <iostream>

namespace {
    /*
     * Preparara la activacion o desactivacion de cada boton despachar
     * dependiendo de si hay pizzas preparadas de ese tipo.
     */
    void obtener_activacion_botones_dependiendo_de_si_hay_preparadas(
        const modelo::PizzasAContadores &contadores,
        ActivacionBotones &activacion_botones
    ) {
        for (auto &[tp, contadores_tp] : contadores) {
            activacion_botones.despachar.emplace(
                tp, contadores_tp.preparadas > 0
            );
        }
    }

    PresentacionPreparacionPizzas obtener_vista_preparacion( //
        const ModeloAmplio &modelo_amplio
    ) {
        const auto preparacion =
            modelo_amplio.modelo_interno.obtener_estado_preparacion_pizzas();
        return presentador::estado_preparacion_pizzas_to_vista(preparacion);
    }

    PizzasToStrings obtener_vista_preparadas( //
        const ModeloAmplio &modelo_amplio
    ) {
        const modelo::PizzasAContadores &contadores =
            modelo_amplio.modelo_interno.control_pizzas.contadores;
        return presentador::contadores_to_preparadas(contadores);
    }
    PresentacionPedidos obtener_presentacion_pedidos( //
        const ModeloAmplio &modelo_amplio
    ) {
        const auto &pedidos =
            modelo_amplio.modelo_interno.control_pizzas.pedidos;
        const auto presentacion_pedidos =
            presentador::crear_presentacion_pedidos(pedidos);
        return presentacion_pedidos;
    }

} // namespace

ActivacionBotones enlace_vista_impl::obtener_activacion_botones( //
    const ModeloInterno &modelo_interno
) {
    const auto &control_pizzas = modelo_interno.control_pizzas;
    // Activacion botones despachar
    const modelo::PizzasAContadores &contadores = control_pizzas.contadores;
    ActivacionBotones activacion_botones;
    obtener_activacion_botones_dependiendo_de_si_hay_preparadas(
        contadores, activacion_botones
    );

    // Activacion botones encargar
    constexpr int maximo = modelo_info::MAXIMO_PIZZAS_EN_PREPARACION;
    const auto en_preparacion = modelo_interno.encargos.total();
    assert(en_preparacion <= maximo);
    const bool se_pueden_preparar_mas = en_preparacion < maximo;
    activacion_botones.encargar = se_pueden_preparar_mas;
    return activacion_botones;
}

///////////////////////////////////////////
// EnlaceVista (public)
//////////////////////////////////////////

EnlaceVista::EnlaceVista() {}

void EnlaceVista::set_vista(std::shared_ptr<Vista> vista_) { vista = vista_; }

void EnlaceVista::on_cambio_de_fase(FaseNivel nueva_fase) {
    LOG(info) << "Cambio de fase en EnlaceVista: "
              << static_cast<int>(nueva_fase);
    switch (nueva_fase) {
        case FaseNivel::MostrandoInstrucciones:
            vista->cambiar_visibilidad_instrucciones(true);
            break;
        case FaseNivel::Activa:
            vista->cambiar_visibilidad_instrucciones(false);
            vista->mostrar_elementos_fase_activa();
            break;
        case FaseNivel::EsperaAntesDeResultado:
            vista->esconder_botones_gestion_pizzeria();
            break;
        case FaseNivel::MostrandoResultado:
            vista->cambiar_visibilidad_resultado(true);
            break;
        case FaseNivel::Reiniciando:
            vista->cambiar_visibilidad_resultado(false);
            break;
        default:
            break;
    }
}

void EnlaceVista::esconder_paneles() const { vista->paneles->visible = false; }

void EnlaceVista::actualizar_interfaz_grafico(
    const ModeloAmplio &modelo_amplio //
) {
    const sf::Time tiempo_real = modelo_amplio.obtener_tiempo_transcurrido();
    const auto activacion_botones =
        enlace_vista_impl::obtener_activacion_botones(
            modelo_amplio.modelo_interno
        );
    vista->activar_botones_condicionalmente(activacion_botones);
    std::optional<PresentacionPreparacionPizzas> info_preparacion;
    std::optional<PizzasToStrings> info_preparadas;
    std::optional<const PresentacionPedidos> info_pedidos;

    const auto fase_actual = modelo_amplio.get_fase_actual();

    if ( //
        fase_actual == FaseNivel::Activa ||
        fase_actual == FaseNivel::EsperaAntesDeResultado
    ) {
        info_preparacion.emplace(obtener_vista_preparacion(modelo_amplio));
        info_preparadas.emplace(obtener_vista_preparadas(modelo_amplio));
        info_pedidos.emplace(obtener_presentacion_pedidos(modelo_amplio));
    }
    const auto mostrando_grid = modelo_amplio.mostrando_grid;
    const auto tiempo_juego =
        modelo_amplio.modelo_interno.obtener_tiempo_juego();

    auto info_barra_estado =
        presentador::crea_vista_barra_estado(tiempo_real, tiempo_juego);
    PresentacionGeneral presentacion{
        mostrando_grid, info_preparacion, info_preparadas, info_pedidos,
        info_barra_estado
    };
    vista->actualizar_interfaz_grafico(presentacion);
}

const std::shared_ptr<const BotonesApp> EnlaceVista::get_botones() const {
    return vista->botones;
}

std::shared_ptr<VistaObservable> EnlaceVista::get_vista() const { //
    return vista;
}

void EnlaceVista::dibujar_vista(sf::RenderTarget &target) { //
    target.draw(*vista);
}