#include "paneles.h"
#include "../shared/log_init.h"
#include "../templates/dibujar_elementos.h"
#include "basicos_vista.h"
#include "botones_despachar.h"
#include "botones_encargar.h"
#include "componentes/boton_con_texto.h"
#include "componentes/etiqueta.h"
#include "etiquetas/etiquetas.h"
#include "etiquetas/etiquetas_pedidos.h"
#include <cassert>

namespace medidas {
    constexpr float GROSOR_BORDE_PANEL = 3;
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
      encargar(crear_botones_encargar(tp_disponibles)) {
    for (auto [_, btn] : encargar) {
        add_child(btn);
    }
}

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
    const PresentacionPreparacionPizzas &presentacion //
) {
    auto pos_panel = basicos_vista::obtener_posicion_panel( //
        IndicePanel::PANEL_EN_PREPARACION
    );
    for (auto bpn : barras_progreso_con_nombres) {
        remove_child(bpn);
    }
    barras_progreso_con_nombres = crear_barras_progreso( //
        presentacion, pos_panel
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
    IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta,
    const dominio::TiposDePizza &tp_disponibles
)
    : Panel(indice, etiqueta),
      despachar(crear_botones_despachar(tp_disponibles)) {
    etiquetas_preparadas =
        std::make_shared<EtiquetasPreparadas>(tp_disponibles);
    add_child(etiquetas_preparadas);
    for (auto [_, btn] : despachar) {
        add_child(btn);
    }
}

void PanelPreparadas::actualizar(          //
    const PizzasToStrings &info_preparadas //
) {
    etiquetas_preparadas->actualizar(info_preparadas);
}

void PanelPreparadas::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    Panel::draw(target, states);
    target.draw(*etiquetas_preparadas);
    for (auto &[_, boton_ptr] : despachar) {
        assert(boton_ptr != nullptr);
        boton_ptr->actualizar();
        target.draw(*boton_ptr);
    }
}

///////////////////////////////////////////
// PanelPedidos (public)
/////////////////////////////////////////

PanelPedidos::PanelPedidos(
    IndicePanel indice, std::shared_ptr<Etiqueta> etiqueta

)
    : Panel(indice, etiqueta) {
    etiquetas_pedidos = std::make_shared<EtiquetasPedidos>();
    add_child(etiquetas_pedidos);
}

void PanelPedidos::actualizar(const PresentacionPedidos &presentacion_pedidos //
) {
    etiquetas_pedidos->actualizar(presentacion_pedidos);
}

void PanelPedidos::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    Panel::draw(target, states);
    target.draw(*etiquetas_pedidos);
}

///////////////////////////////////////////
// Paneles (public)
/////////////////////////////////////////
// TODO: ver si es necesario pasar etiqueta a los paneles
Paneles::Paneles(const dominio::TiposDePizza &tp_disponibles) {
    const FabricaEtiquetasTituloPanel fabrica;
    LOG(debug) << "A punto de crear los paneles";
    for (auto indice : paneles_posibles) {
        std::shared_ptr<Panel> panel;
        auto titulo = fabrica.crearEtiquetaTituloPanel(
            basicos_vista::obtener_posicion_panel(indice), //
            texto_titulos_paneles.at(indice)
        );
        switch (indice) {
            case IndicePanel::PANEL_ENCARGAR:
                panel = std::make_shared<PanelEncargar>( //
                    indice, titulo, tp_disponibles
                );
                break;
            case IndicePanel::PANEL_EN_PREPARACION:
                panel = std::make_shared<PanelEnPreparacion>(indice, titulo);
                break;
            case IndicePanel::PANEL_PREPARADAS:
                panel = std::make_shared<PanelPreparadas>(
                    indice, titulo, tp_disponibles
                );
                break;
            case IndicePanel::PANEL_PEDIDOS:
                panel = std::make_shared<PanelPedidos>(indice, titulo);
                break;
            default:
                assert(false && "Panel desconocido");
                break;
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

std::shared_ptr<PanelPreparadas> Paneles::get_panel_preparadas() {
    auto panel = _paneles.at(IndicePanel::PANEL_PREPARADAS);
    auto panel_preparadas = std::dynamic_pointer_cast<PanelPreparadas>(panel);
    assert(panel_preparadas);
    return panel_preparadas;
}

void Paneles::actualizar(
    const PresentacionPreparacionPizzas &info_preparacion, //
    const PizzasToStrings &info_preparadas,                //
    const PresentacionPedidos &info_pedidos                //
) {
    if (!visible)
        return;

    Panel *panel_;
    {
        panel_ = _paneles.at(IndicePanel::PANEL_EN_PREPARACION).get();
        auto *panel = dynamic_cast<PanelEnPreparacion *>(panel_);
        assert(panel);
        panel->actualizar(info_preparacion);
    }
    {
        panel_ = _paneles.at(IndicePanel::PANEL_PREPARADAS).get();
        auto *panel = dynamic_cast<PanelPreparadas *>(panel_);
        assert(panel);
        panel->actualizar(info_preparadas);
    }
    {
        panel_ = _paneles.at(IndicePanel::PANEL_PEDIDOS).get();
        auto *panel = dynamic_cast<PanelPedidos *>(panel_);
        assert(panel);
        panel->actualizar(info_pedidos);
    }
}

bool Paneles::get_visibilidad() const { //
    return visible;
};

void Paneles::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    if (!visible)
        return;
    dibujar_elementos(target, _paneles);
}
