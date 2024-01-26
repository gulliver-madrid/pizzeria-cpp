#include "paneles.h"
#include "../shared/log_init.h"
#include "../templates/dibujar_elementos.h"
#include "basicos_vista.h"
#include "botones_encargar.h"
#include "componentes/etiqueta.h"
#include "etiquetas/etiquetas.h"
#include <cassert>

namespace medidas {
    constexpr int GROSOR_BORDE_PANEL = 3;
} // namespace medidas

const std::map<IndicePanel, std::string> texto_titulos_paneles = {
    {IndicePanel::PANEL_ENCARGAR, "Encargar"},
    {IndicePanel::PANEL_EN_PREPARACION, "En preparaci%on"},
    {IndicePanel::PANEL_PREPARADAS, "Preparadas"},
    {IndicePanel::PANEL_PEDIDOS, "Pedidos"}
};

namespace {
    sf::RectangleShape _crearPanelVertical(float x, float y) {
        auto rect = sf::RectangleShape(
            sf::Vector2f(medidas::ANCHO_PANEL, medidas::ALTO_PANEL)
        );
        rect.setPosition(sf::Vector2f(x, y));
        rect.setFillColor(sf::Color(40, 40, 40, 200));
        rect.setOutlineColor(sf::Color::Green);
        rect.setOutlineThickness(medidas::GROSOR_BORDE_PANEL);
        return rect;
    }

    sf::RectangleShape crear_panel_estandar(IndicePanel indice) {
        auto pos_panel = basicos_vista::obtener_posicion_panel(indice);
        return _crearPanelVertical(pos_panel.x, pos_panel.y);
    }
} // namespace

///////////////////////////////////////////
// Panel (public)
/////////////////////////////////////////

Panel::Panel(IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta)
    : indice(indice), forma(crear_panel_estandar(indice)),
      etiqueta_titulo(etiqueta) {
    add_child(etiqueta_titulo);
}

void Panel::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    target.draw(forma);
    target.draw(*etiqueta_titulo);
}

///////////////////////////////////////////
// PanelEncargar (public)
/////////////////////////////////////////

PanelEncargar::PanelEncargar(
    IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta,
    const dominio::TiposDePizza &tp_disponibles
)
    : Panel(indice, etiqueta),
      encargar(_crear_botones_encargar(tp_disponibles)) {
    for (auto [_, btn] : encargar) {
        add_child(btn);
    }
}

void PanelEncargar::actualizar(
    const VistaPreparacionPizzas &vista_preparacion //
) {}

void PanelEncargar::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    Panel::draw(target, states);
    for (auto &[_, boton_ptr] : encargar) {
        assert(boton_ptr != nullptr);
        boton_ptr->actualizar();
        target.draw(*boton_ptr);
    }
}

///////////////////////////////////////////
// PanelEnPreparacion (public)
/////////////////////////////////////////

PanelEnPreparacion::PanelEnPreparacion(
    IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta
)
    : Panel(indice, etiqueta) {}

void PanelEnPreparacion::actualizar(
    const VistaPreparacionPizzas &vista_preparacion //
) {
    auto pos_panel = basicos_vista::obtener_posicion_panel( //
        IndicePanel::PANEL_EN_PREPARACION
    );
    for (auto bpn : barras_progreso_con_nombres) {
        remove_child(bpn);
    }
    barras_progreso_con_nombres = crear_barras_progreso( //
        vista_preparacion, pos_panel
    );
    for (auto bpn : barras_progreso_con_nombres) {
        add_child(bpn);
    }
}

void PanelEnPreparacion::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    Panel::draw(target, states);
    for (auto bpn : barras_progreso_con_nombres) {
        target.draw(*bpn);
    }
}

///////////////////////////////////////////
// PanelPreparadas (public)
/////////////////////////////////////////

PanelPreparadas::PanelPreparadas(
    IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta
)
    : Panel(indice, etiqueta) {
    etiquetas_preparadas = std::make_shared<EtiquetasPreparadas>();
    LOG(debug) << "antes de add child de etiquetas preparadas";
    add_child(etiquetas_preparadas);
    LOG(debug) << "despues de add child de etiquetas preparadas";
}

void PanelPreparadas::setup(const dominio::TiposDePizza &tp_disponibles) {
    assert(etiquetas_preparadas);
    LOG(debug) << "antes del setup de etiquetas preparadas";
    etiquetas_preparadas->setup(tp_disponibles);
}

void PanelPreparadas::actualizar(           //
    const PizzasToStrings &vista_preparadas //
) {
    etiquetas_preparadas->actualizar(vista_preparadas);
}

void PanelPreparadas::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    Panel::draw(target, states);
    target.draw(*etiquetas_preparadas);
}

///////////////////////////////////////////
// Paneles (public)
/////////////////////////////////////////

Paneles::Paneles(const dominio::TiposDePizza &tp_disponibles) {
    const FabricaEtiquetasTituloPanel fabrica(font);
    LOG(debug) << "A punto de crear los paneles";
    for (auto indice : paneles_posibles) {
        std::shared_ptr<Panel> panel = nullptr;
        auto titulo = fabrica.crearEtiquetaTituloPanel(
            basicos_vista::obtener_posicion_panel(indice), //
            texto_titulos_paneles.at(indice)
        );

        if (indice == IndicePanel::PANEL_ENCARGAR) {
            panel = std::make_shared<PanelEncargar>( //
                indice, titulo, tp_disponibles
            );
        } else if (indice == IndicePanel::PANEL_EN_PREPARACION) {
            panel = std::make_shared<PanelEnPreparacion>(indice, titulo);
        } else if (indice == IndicePanel::PANEL_PREPARADAS) {
            panel = std::make_shared<PanelPreparadas>(indice, titulo);
            auto &panel_preparadas = dynamic_cast<PanelPreparadas &>(*panel);
            LOG(debug) << "A punto de hacer el setup de panel preparadas";
            panel_preparadas.setup(tp_disponibles);
            LOG(debug) << "Despues del setup de panel preparadas";
        } else {
            panel = std::make_shared<Panel>(indice, titulo);
        }

        _paneles.emplace(indice, panel);
        add_child(panel);
    }
    LOG(debug) << "Paneles creados";
}

std::shared_ptr<PanelEncargar> Paneles::get_panel_encargar() {
    auto panel = _paneles.at(IndicePanel::PANEL_ENCARGAR);
    auto panel_encargar = std::dynamic_pointer_cast<PanelEncargar>(panel);
    assert(panel_encargar);
    return panel_encargar;
}

void Paneles::actualizar(                            //
    const VistaPreparacionPizzas &vista_preparacion, //
    const PizzasToStrings &vista_preparadas          //
) {
    if (!visible)
        return;

    Panel *panel_en_prep = _paneles.at(IndicePanel::PANEL_EN_PREPARACION).get();
    PanelEnPreparacion *panel_en_preparacion =
        dynamic_cast<PanelEnPreparacion *>(panel_en_prep);
    assert(panel_en_preparacion != nullptr);
    panel_en_preparacion->actualizar(vista_preparacion);

    Panel *panel_prep = _paneles.at(IndicePanel::PANEL_PREPARADAS).get();
    PanelPreparadas *panel_preparadas =
        dynamic_cast<PanelPreparadas *>(panel_prep);
    assert(panel_preparadas != nullptr);
    panel_preparadas->actualizar(vista_preparadas);
}

void Paneles::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    if (!visible)
        return;
    dibujar_elementos(target, _paneles);
}
