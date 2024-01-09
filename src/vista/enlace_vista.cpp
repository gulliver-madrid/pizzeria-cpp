#include "enlace_vista.h"
#include "../estado_nivel.h"
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

ActivacionBotones impl::obtener_activacion_botones( //
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

void EnlaceVista::on_cambio_a_fase_activa() const {
    vista->mostrar_elementos_fase_activa();
}

void EnlaceVista::on_cambio_a_fase_espera_antes_de_resultado() const {
    vista->esconder_botones_gestion_pizzeria();
}

void EnlaceVista::esconder_paneles() const {
    vista->paneles_completos.visible = false;
}

void EnlaceVista::actualizarIU(
    sf::RenderTarget &(target),        //
    const Estado &estado,              //
    const sf::Time &tiempo_real_actual //
) {
    const auto activacion_botones =
        impl::obtener_activacion_botones(estado.modelo_interno);
    vista->activar_botones_condicionalmente(activacion_botones);
    vista->actualizarIU(target, estado, tiempo_real_actual);
}
