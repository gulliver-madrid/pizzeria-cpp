#include "vista.h"
#include "../shared/dev.h"
#include "../shared/log_init.h"
#include "../templates/helpers.h"
#include "basicos_vista.h"
#include "botones/botones_app.h"
#include "componentes/boton_con_texto.h"
#include "etiquetas/etiquetas.h"
#include "grid.h"
#include "paneles.h"
#include "vista_data.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>
#include <map>
#include <string>

using dominio::TipoPizza;
using dominio::TiposDePizza;

namespace {
    /*
     * Activa o desactiva cada boton despachar segun proceda.
     */
    void activar_botones_despachar_condicionalmente(
        TipoPizzaToBoton &botones_despachar,
        const ActivacionBotones &activacion_botones
    ) {
        for (auto &[tp, debe_estar_activo] : activacion_botones.despachar) {
            assert(has_key(botones_despachar, tp));
            auto &boton_despachar = botones_despachar.at(tp);
            boton_despachar->activacion_condicional(debe_estar_activo);
        }
    }

} // namespace

///////////////////////////////////////////
// Vista (private)
//////////////////////////////////////////

/* Actualiza las etiquetas */
void Vista::_actualizar_etiquetas(const VistaBarraEstado &info_barra_estado) {
    etiquetas->actualizar_barra_estado(info_barra_estado);
}

void Vista::_actualizar_vista_paneles(const VistasJuego &vistas) {
    paneles->visible = vistas.info_preparacion.has_value();
    if (vistas.info_preparacion) {
        // Estaran definidas las tres o ninguna
        assert(vistas.info_preparacion);
        assert(vistas.info_preparadas);
        assert(vistas.info_pedidos);
        paneles->actualizar(
            vistas.info_preparacion.value(), //
            vistas.info_preparadas.value(),  //
            vistas.info_pedidos.value()      //
        );
    }
}

void Vista::_activar_botones_condicionalmente(
    const ActivacionBotones &activacion_botones
) {
    activar_botones_despachar_condicionalmente(
        botones->despachar, activacion_botones
    );
    for (auto &[_, boton] : botones->encargar) {
        boton->activacion_condicional(activacion_botones.encargar);
    }
}

///////////////////////////////////////////
// Vista (public)
//////////////////////////////////////////

Vista::Vista() {
    LOG(info) << "start constructor de Vista";
    presentacion_vista = std::make_shared<PresentacionVista>();
    LOG(info) << "end constructor de vista";
}

void Vista::setup(
    std::shared_ptr<Grid> grid_,                 //
    const dominio::TiposDePizza &tp_disponibles, //
    const std::string &instrucciones,            //
    const NumNivelOpcional &num_nivel            //
) {
    this->grid = grid_;
    paneles = std::make_shared<Paneles>(tp_disponibles);
    auto panel_encargar = paneles->get_panel_encargar();
    auto panel_preparadas = paneles->get_panel_preparadas();
    auto &botones_encargar = panel_encargar->encargar;
    auto &botones_despachar = panel_preparadas->despachar;
    botones = std::make_shared<BotonesApp>(
        tp_disponibles, botones_encargar, botones_despachar
    );
    LOG(info) << "Inicializando etiquetas" << std::endl;
    etiquetas = std::make_shared<EtiquetasGenerales>();
    etiquetas->setup(
        instrucciones, //
        num_nivel      //
    );
    etiquetas->set_presentacion_vista(presentacion_vista);
    add_child(botones);
    add_child(paneles);
    add_child(etiquetas);

    LOG(info) << "Etiquetas inicializadas" << std::endl;
    // Mostrar botones iniciales
    botones->generales.alternar_grid->visible = MODO_DESARROLLO;
    botones->generales.reiniciar->visible = true;
    botones->generales.salir->visible = true;
    botones->empezar->visible = true;
}

/*
 * Actualiza el interfaz grafico
 */
void Vista::actualizar_interfaz_grafico(const PresentacionGeneral &presentacion
) {
    _mostrando_grid = presentacion.mostrando_grid;
    _actualizar_vista_paneles(presentacion.vistas);
    _actualizar_etiquetas(presentacion.barra_estado);
    _activar_botones_condicionalmente(presentacion.activacion_botones);
}

void Vista::cambiar_visibilidad_instrucciones(bool nueva) {
    presentacion_vista->visibilidad.instrucciones = nueva;
}
void Vista::cambiar_visibilidad_resultado(bool nueva) {
    presentacion_vista->visibilidad.resultado = nueva;
}

void Vista::mostrar_elementos_fase_activa() {
    botones->empezar->visible = false;
    botones->mostrar_botones_nivel(true);
    paneles->visible = true;
}

void Vista::esconder_botones_gestion_pizzeria() { //
    botones->mostrar_botones_nivel(false);
}

std::shared_ptr<const PresentacionVista>
Vista::get_presentacion_vista() const { //
    return presentacion_vista;
}

std::shared_ptr<PanelesObservables> Vista::get_paneles() const { //
    return paneles;
};

void Vista::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    // Limpia la target y pinta los componentes visuales
    target.clear(colores::COLOR_FONDO);
    if (_mostrando_grid) {
        assert(grid);
        grid->draw(target, GRID_SIZE, GRID_TONE);
    }
    target.draw(*paneles);
    target.draw(*etiquetas);
    target.draw(*botones);
}
