#include "enlace_vista.h"
#include "../fase_nivel.h"
#include "../shared/log_init.h"
#include "../templates/helpers.h"
#include "../vista/paneles.h"
#include "presentador.h"
#include "presentador_paneles.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

namespace {
    /*
     * Preparara la activacion o desactivacion de cada boton despachar
     * dependiendo de si hay pizzas preparadas de ese tipo.
     */
    void obtener_activacion_botones_despachar(
        const modelo::PizzasAContadores &contadores,
        ActivacionBotones &activacion_botones
    ) {
        for (auto &[tp, contadores_tp] : contadores) {
            activacion_botones.despachar.emplace(
                tp, contadores_tp.preparadas > 0
            );
        }
    }

    std::shared_ptr<VistasPaneles> generar_vistas_paneles( //
        const ModeloAmplio &modelo_amplio
    ) {
        auto vistas = std::make_shared<VistasPaneles>();
        const auto modelo = modelo_amplio.modelo_interno;
        PresentadorPaneles presentador{modelo};
        vistas->info_preparacion = presentador.obtener_vista_preparacion();
        vistas->info_preparadas = presentador.obtener_vista_preparadas();
        vistas->info_pedidos = presentador.obtener_presentacion_pedidos();
        return vistas;
    }

    bool deben_mostrarse_los_paneles(const ModeloAmplio &modelo) {
        const auto fase_actual = modelo.get_fase_actual();
        return (
            fase_actual == FaseNivel::Activa ||
            fase_actual == FaseNivel::EsperaAntesDeResultado
        );
    }

    std::optional<std::shared_ptr<VistasPaneles>> obtener_vistas_paneles( //
        const ModeloAmplio &modelo
    ) {
        std::optional<std::shared_ptr<VistasPaneles>> vistas;
        if (deben_mostrarse_los_paneles(modelo)) {
            vistas.emplace(generar_vistas_paneles(modelo));
        }
        return vistas;
    }

} // namespace

ActivacionBotones enlace_vista_impl::obtener_activacion_botones( //
    const ModeloInterno &modelo
) {
    // Activacion botones despachar
    ActivacionBotones activacion_botones;
    obtener_activacion_botones_despachar(
        modelo.control_pizzas.contadores, activacion_botones
    );

    // Activacion botones encargar
    activacion_botones.encargar = modelo.encargos.se_pueden_encargar_mas();
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

VistaBarraEstado obtener_vista_barra_estado(const ModeloAmplio &modelo_amplio //
) {
    const sf::Time tiempo_real = modelo_amplio.obtener_tiempo_transcurrido();
    const auto tiempo_juego =
        modelo_amplio.modelo_interno.obtener_tiempo_juego();
    return presentador::crea_vista_barra_estado(tiempo_real, tiempo_juego);
}

void EnlaceVista::actualizar_interfaz_grafico(
    const ModeloAmplio &modelo_amplio //
) {
    const auto activacion_botones =
        enlace_vista_impl::obtener_activacion_botones(
            modelo_amplio.modelo_interno
        );

    const auto vistas_paneles = obtener_vistas_paneles(modelo_amplio);
    const auto mostrando_grid = modelo_amplio.mostrando_grid;

    const auto info_barra_estado = obtener_vista_barra_estado(modelo_amplio);

    PresentacionGeneral presentacion{
        mostrando_grid,    //
        vistas_paneles,    //
        info_barra_estado, //
        activacion_botones //
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
