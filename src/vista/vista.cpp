#include "vista.h"
#include "../fase_nivel.h"
#include "../shared/dev.h"
#include "../shared/log_init.h"
#include "../shared/num_nivel.h"
#include "../templates/helpers.h"
#include "basicos_vista.h"
#include "grid.h"
#include "presentador.h"
#include "vista_data.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>
#include <iostream>
#include <map>
#include <string>

using dominio::TipoPizza;
using dominio::TiposDePizza;

namespace {
    /*
     * Activa o desactiva cada boton despachar segun proceda.
     */
    void activar_botones_despachar_si_procede(
        TipoPizzaToBoton &botones_despachar,
        const ActivacionBotones &activacion_botones
    ) {
        for (auto &[tp, debe_estar_activo] : activacion_botones.despachar) {
            assert(has_key(botones_despachar, tp));
            auto &boton_despachar = botones_despachar.at(tp);
            boton_despachar.activacion_condicional(debe_estar_activo);
        }
    }

} // namespace

///// Vista (private) /////

// TODO:  separar la parte de actualizacion y de dibujo
// TODO:  ir pasando a enlace_vista la logica que deba conocer el modelo
/* Actualiza y dibuja las etiquetas */
void Vista::_actualizar_etiquetas(
    sf::RenderTarget &target,          //
    const ModeloAmplio &modelo_amplio, //
    const sf::Time &tiempo_real_actual //
) {
    const modelo::PizzasAContadores &contadores =
        modelo_amplio.modelo_interno.control_pizzas.contadores;

    auto pedidos = modelo_amplio.modelo_interno.control_pizzas.pedidos;
    _deben_dibujarse_etiquetas_contadores = false;
    switch (modelo_amplio.get_fase_actual()) {
        case FaseNivel::MostrandoInstrucciones:
            break;
        case FaseNivel::Activa:
        case FaseNivel::EsperaAntesDeResultado:
            {
                const auto vista_preparadas =
                    presentador::contadores_to_preparadas(contadores);
                etiquetas->actualizar_contadores(vista_preparadas, pedidos);
                _deben_dibujarse_etiquetas_contadores = true;

                break;
            }
        default:
            break;
    }

    const auto tiempo_juego_actual =
        modelo_amplio.modelo_interno.obtener_tiempo_juego();
    etiquetas->actualizar_barra_estado(tiempo_real_actual, tiempo_juego_actual);
    etiquetas->dibujar_barra_estado(target);
}

void Vista::_dibujar_paneles(sf::RenderTarget &target) const {
    // TODO: usar el sistema nativo de dibujo de SFML.
    target.draw(*paneles);
}

void Vista::_actualizar_vista_paneles(
    const std::optional<VistaPreparacionPizzas> &vista_preparacion

) {
    paneles->visible = vista_preparacion.has_value();
    if (vista_preparacion) {
        paneles->actualizar(vista_preparacion.value());
    }
}

///// Vista (public) /////

Vista::Vista() {}

void Vista::setup(
    const OptionalFont &font,                    //
    std::shared_ptr<Grid> grid,                  //
    const dominio::TiposDePizza &tp_disponibles, //
    const std::string &instrucciones,            //
    const NumNivelOpcional &num_nivel            //
) {
    this->grid = grid;
    botones = std::make_shared<BotonesApp>(font, tp_disponibles);
    paneles = std::make_shared<Paneles>(font);
    LOG(info) << "Inicializando etiquetas" << std::endl;
    etiquetas = std::make_shared<EtiquetasGenerales>(font);
    etiquetas->setup(
        instrucciones, //
        num_nivel,     //
        tp_disponibles //
    );
    LOG(info) << "Etiquetas inicializadas" << std::endl;
    // Mostrar botones iniciales
    botones->generales.alternar_grid.visible = MODO_DESARROLLO;
    botones->generales.reiniciar.visible = true;
    botones->generales.salir.visible = true;
    botones->empezar.visible = true;
}

void Vista::set_presentacion_vista(
    std::shared_ptr<PresentacionVista> presentacion_vista //
) {
    this->presentacion_vista = presentacion_vista;
    etiquetas->set_presentacion_vista(presentacion_vista);
}

/*
 * Actualiza el interfaz grafico
 */
void Vista::actualizarIU(                                           //
    sf::RenderTarget &target,                                       //
    const ModeloAmplio &modelo_amplio,                              //
    const std::optional<VistaPreparacionPizzas> &vista_preparacion, //
    const sf::Time &tiempo_real_actual                              //
) {

    // Limpia la target y empieza a pintar los componentes visuales
    target.clear(colores::COLOR_FONDO);
    if (modelo_amplio.mostrando_grid) {
        assert(grid);
        grid->draw(target, GRID_SIZE, GRID_TONE);
    }
    const auto fase_actual = modelo_amplio.get_fase_actual();

    _actualizar_vista_paneles(vista_preparacion);
    _actualizar_etiquetas(target, modelo_amplio, tiempo_real_actual);
}

void Vista::mostrar_elementos_fase_activa() {
    botones->empezar.visible = false;
    botones->mostrar_botones_nivel(true);
    paneles->visible = true;
}

void Vista::esconder_botones_gestion_pizzeria() { //
    botones->mostrar_botones_nivel(false);
}

void Vista::activar_botones_condicionalmente(
    const ActivacionBotones &activacion_botones
) {
    activar_botones_despachar_si_procede(
        botones->despachar, activacion_botones
    );
    for (auto &[_, boton] : botones->encargar) {
        boton.activacion_condicional(activacion_botones.encargar);
    }
}

std::shared_ptr<PanelesObservables> Vista::get_paneles() const { //
    return paneles;
};

void Vista::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    _dibujar_paneles(target);
    etiquetas->dibujar_info(target);
    if (_deben_dibujarse_etiquetas_contadores) {
        etiquetas->dibujar_preparadas(target);
        etiquetas->dibujar_pedidos(target);
    }
    target.draw(*botones);
}
