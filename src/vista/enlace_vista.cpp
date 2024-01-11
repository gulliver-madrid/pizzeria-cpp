#include "enlace_vista.h"
#include "../fase_nivel.h"
#include "../log_init.h"
#include "../templates/helpers.h"
#include "vista.h"
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

void EnlaceVista::cambiar_visibilidad_instrucciones(bool nueva) {
    presentacion_vista->etiquetas_info.mostrar_instrucciones = nueva;
}
void EnlaceVista::cambiar_visibilidad_resultado(bool nueva) {
    LOG(debug) << "Cambiando visibilidad resultado: " << nueva;
    presentacion_vista->etiquetas_info.mostrar_resultado = nueva;
}

///// EnlaceVista (public) /////

EnlaceVista::EnlaceVista() {
    presentacion_vista = std::make_shared<PresentacionVista>();
}

void EnlaceVista::set_vista(std::shared_ptr<Vista> vista) {
    this->vista = vista;
    vista->set_presentacion_vista(presentacion_vista);
}

void EnlaceVista::on_cambio_de_fase(FaseNivel nueva_fase) {
    LOG(debug) << "Cambio de fase en EnlaceVista: "
               << static_cast<int>(nueva_fase);
    switch (nueva_fase) {
        case FaseNivel::MostrandoInstrucciones:
            cambiar_visibilidad_instrucciones(true);
            break;
        case FaseNivel::Activa:
            cambiar_visibilidad_instrucciones(false);
            vista->mostrar_elementos_fase_activa();
            break;
        case FaseNivel::EsperaAntesDeResultado:
            vista->esconder_botones_gestion_pizzeria();
            break;
        case FaseNivel::MostrandoResultado:
            cambiar_visibilidad_resultado(true);
            break;
        case FaseNivel::Reiniciando:
            cambiar_visibilidad_resultado(false);
            break;
        default:
            break;
    }
}

void EnlaceVista::esconder_paneles() const {
    vista->paneles_completos.visible = false;
}

void EnlaceVista::actualizar_interfaz_grafico(
    sf::RenderTarget &target,          //
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

PresentacionVista EnlaceVista::get_presentacion_vista() const { //
    return *presentacion_vista;
}
void EnlaceVista::dibujar_vista(sf::RenderTarget &target) { //
    target.draw(*vista);
}
