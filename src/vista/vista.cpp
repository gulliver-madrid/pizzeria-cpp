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
            boton_despachar->activacion_condicional(debe_estar_activo);
        }
    }

} // namespace

///////////////////////////////////////////
// Vista (private)
//////////////////////////////////////////

// TODO:  ir pasando a enlace_vista la logica que deba conocer el modelo
/* Actualiza las etiquetas */
void Vista::_actualizar_etiquetas(
    std::optional<const PresentacionPedidos> &info_pedidos, //
    const sf::Time &tiempo_real_actual,                     //
    const sf::Time &tiempo_juego_actual                     //
) {
    if (info_pedidos) {
        etiquetas->actualizar_pedidos(info_pedidos.value());
    }

    _deben_dibujarse_etiquetas_pedidos = info_pedidos.has_value();
    etiquetas->actualizar_barra_estado(tiempo_real_actual, tiempo_juego_actual);
}

void Vista::_actualizar_vista_paneles(
    const std::optional<PresentacionPreparacionPizzas> &info_preparacion,
    const std::optional<PizzasToStrings> &info_preparadas
) {
    paneles->visible = info_preparacion.has_value();
    if (info_preparacion) {
        // Estaran definidas las dos o ninguna
        assert(info_preparacion);
        paneles->actualizar(info_preparacion.value(), info_preparadas.value());
    }
}

///////////////////////////////////////////
// Vista (public)
//////////////////////////////////////////

Vista::Vista() {}

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

void Vista::set_presentacion_vista(
    std::shared_ptr<PresentacionVista> presentacion_vista_ //
) {
    this->presentacion_vista = presentacion_vista_;
    etiquetas->set_presentacion_vista(presentacion_vista);
}

/*
 * Actualiza el interfaz grafico
 */
void Vista::actualizar_interfaz_grafico(
    bool mostrando_grid,                                                  //
    FaseNivel fase_actual,                                                //
    const std::optional<PresentacionPreparacionPizzas> &info_preparacion, //
    std::optional<PizzasToStrings> &info_preparadas,                      //
    std::optional<const PresentacionPedidos> &info_pedidos,               //
    const sf::Time &tiempo_real_actual,                                   //
    const sf::Time &tiempo_juego_actual                                   //
) {
    _mostrando_grid = mostrando_grid;
    _actualizar_vista_paneles(info_preparacion, info_preparadas);
    _actualizar_etiquetas(
        info_pedidos, tiempo_real_actual, tiempo_juego_actual
    );
}

void Vista::mostrar_elementos_fase_activa() {
    botones->empezar->visible = false;
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
        boton->activacion_condicional(activacion_botones.encargar);
    }
}

std::shared_ptr<PanelesObservables> Vista::get_paneles() const { //
    return paneles;
};

void Vista::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    // Limpia la target y empieza a pintar los componentes visuales
    target.clear(colores::COLOR_FONDO);
    if (_mostrando_grid) {
        assert(grid);
        grid->draw(target, GRID_SIZE, GRID_TONE);
    }
    etiquetas->dibujar_barra_estado(target);
    target.draw(*paneles);
    etiquetas->dibujar_info(target);
    if (_deben_dibujarse_etiquetas_pedidos) {
        etiquetas->dibujar_pedidos(target);
    }
    target.draw(*botones);
}
