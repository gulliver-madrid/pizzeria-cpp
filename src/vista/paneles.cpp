#include "paneles.h"
#include "../shared/log_init.h"
#include "../templates/dibujar_elementos.h"
#include "basicos_vista.h"
#include "etiquetas/etiquetas.h"
#include <cassert>
#include <iostream>

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

Panel::Panel(IndicePanel indice, sf::Text etiqueta)
    : indice(indice), forma(crear_panel_estandar(indice)),
      etiqueta_titulo(etiqueta) {}

void Panel::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    target.draw(forma);
    target.draw(etiqueta_titulo);
}

///////////////////////////////////////////
// PanelEnPreparacion (public)
/////////////////////////////////////////

PanelEnPreparacion::PanelEnPreparacion(
    IndicePanel indice, sf::Text etiqueta, const OptionalFont &font
)
    : Panel(indice, etiqueta), ObjetoConFont(font) {}

void PanelEnPreparacion::actualizar(
    const VistaPreparacionPizzas &vista_preparacion //
) {
    auto pos_panel = basicos_vista::obtener_posicion_panel( //
        IndicePanel::PANEL_EN_PREPARACION
    );
    barras_progreso_con_nombres = crear_barras_progreso( //
        vista_preparacion, pos_panel, font
    );
}

void PanelEnPreparacion::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    Panel::draw(target, states);
    for (auto &bpn : barras_progreso_con_nombres) {
        target.draw(bpn);
    }
}

///////////////////////////////////////////
// PanelPreparadas (public)
/////////////////////////////////////////

PanelPreparadas::PanelPreparadas(IndicePanel indice, sf::Text etiqueta)
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

Paneles::Paneles(
    const dominio::TiposDePizza &tp_disponibles, const OptionalFont &font
)
    : ObjetoConFont(font) {
    const FabricaEtiquetasTituloPanel fabrica(font);
    LOG(debug) << "A punto de crear los paneles";
    for (auto indice : paneles_posibles) {
        std::unique_ptr<Panel> panel = nullptr;
        auto titulo = fabrica.crearEtiquetaTituloPanel(
            basicos_vista::obtener_posicion_panel(indice), //
            texto_titulos_paneles.at(indice)
        );
        if (indice == IndicePanel::PANEL_EN_PREPARACION) {
            panel = std::make_unique<PanelEnPreparacion>(
                indice, std::move(titulo), font
            );
        } else if (indice == IndicePanel::PANEL_PREPARADAS) {
            LOG(debug) << "A punto de crear panel preparadas";
            panel =
                std::make_unique<PanelPreparadas>(indice, std::move(titulo));
            LOG(debug) << "A punto de obtener un puntero a panel preparadas";
            auto &panel_preparadas = dynamic_cast<PanelPreparadas &>(*panel);
            // Por ahora es necesario pasar la fuente antes del setup
            // porque despues no hay manera de pasarla a las instancias
            // de sf::Text
            LOG(debug) << "A punto de establecer la fuente de panel preparadas";
            // Solo fuera de tests
            // assert(font.exists());
            panel_preparadas.set_font(font);
            LOG(debug) << "A punto de hacer el setup de panel preparadas";
            panel_preparadas.setup(tp_disponibles);
            LOG(debug) << "Despues del setup de  panel preparadas";
        } else {
            panel = std::make_unique<Panel>(indice, std::move(titulo));
        }
        _paneles.emplace(indice, std::move(panel));
    }
    LOG(debug) << "Paneles creados";
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
    sf::RenderStates states   //
) const {
    if (!visible)
        return;
    dibujar_elementos(target, _paneles);
}
