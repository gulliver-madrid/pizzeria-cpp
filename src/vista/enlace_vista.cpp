#include "enlace_vista.h"
#include "../fase_nivel.h"
#include "../modelo_amplio/modelo_amplio.h"
#include "../templates/helpers.h"
#include "vista.h"
#include <cassert>

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
    const int en_preparacion = modelo_interno.encargos.total();
    assert(en_preparacion <= maximo);
    const bool se_pueden_preparar_mas = en_preparacion < maximo;
    activacion_botones.encargar = se_pueden_preparar_mas;
    return activacion_botones;
}

///// EnlaceVista (private) /////

void EnlaceVista::on_cambio_a_fase_activa() const {
    vista->mostrar_elementos_fase_activa();
}

void EnlaceVista::on_cambio_a_fase_espera_antes_de_resultado() const {
    vista->esconder_botones_gestion_pizzeria();
}

///// EnlaceVista (private) /////

void EnlaceVista::on_cambio_de_fase(FaseNivel &nueva_fase) {
    switch (nueva_fase) {
        case FaseNivel::Activa:
            on_cambio_a_fase_activa();
            break;
        case FaseNivel::EsperaAntesDeResultado:
            on_cambio_a_fase_espera_antes_de_resultado();
            break;
        default:
            break;
    }
}

void EnlaceVista::esconder_paneles() const {
    vista->paneles_completos.visible = false;
}

void EnlaceVista::actualizarIU(
    sf::RenderTarget &(target),        //
    const ModeloAmplio &modelo_amplio, //
    const sf::Time &tiempo_real_actual //
) {
    const auto activacion_botones =
        enlace_vista_impl::obtener_activacion_botones(
            modelo_amplio.modelo_interno
        );
    vista->activar_botones_condicionalmente(activacion_botones);
    vista->actualizarIU(target, modelo_amplio, tiempo_real_actual);
}
