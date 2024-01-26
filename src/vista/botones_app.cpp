#include "botones_app.h"
#include "../modelo/dominio.h"
#include "../shared/log_init.h"
#include "../templates/helpers.h"
#include "basicos_vista.h"
#include "componentes/botones.h"
#include "componentes/crear_etiqueta.h"
#include "datos_botones.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <cassert>
#include <iterator> // para back_inserter
#include <memory>

using std::vector;

namespace {

    const vector<BotonData> datos_botones_generales = {
        {"Salir", sf::Color::Red},             //
        {"Reiniciar", sf::Color(255, 120, 0)}, //
        {"Alternar Grid", sf::Color::Blue}     //
    };

    const BotonData boton_data_botones_despachar{
        "Despachar", colores::botones_despachar::FONDO,
        colores::botones_despachar::TEXTO
    };

    const BotonData boton_data_empezar{
        "Empezar", sf::Color::Green, sf::Color::Black
    };

    TipoPizzaToBoton _crear_botones_despachar(
        const OptionalFont &font,                   //
        const dominio::TiposDePizza &tp_disponibles //
    ) {
        TipoPizzaToBoton botones;
        const double escala = 0.7;
        const int dif_vertical = 50;
        const int pequeno_ajuste = (-5);

        const auto rect_panel = basicos_vista::obtener_rect_panel( //
            IndicePanel::PANEL_PREPARADAS
        );

        const auto pos_inicial_relativa_al_panel = sf::Vector2f(
            medidas::MARGEN_IZQ_ETIQUETAS + (medidas::ANCHO_PANEL * 0.55),
            medidas::FILA_CONTENIDO_PANEL + pequeno_ajuste
        );

        // Crea los botones
        vector<std::shared_ptr<BotonConTexto>> ordenados;
        for (auto tp : tp_disponibles) {
            auto boton = std::make_shared<BotonConTexto>(
                boton_data_botones_despachar, escala
            );
            botones.insert(std::make_pair(tp, boton));
            assert(has_key(botones, tp));
            botones.at(tp)->establecer_contenedor(rect_panel);
            ordenados.push_back(botones.at(tp));
        }

        // Posiciona los botones
        colocar_botones_en_vertical(
            ordenados, pos_inicial_relativa_al_panel, dif_vertical
        );
        return botones;
    }

    sf::Vector2f _obtener_pos_dcha_botones_generales() {
        const sf::Vector2f pos_ultimo_panel =
            basicos_vista::obtener_posicion_panel( //
                IndicePanel::PANEL_PEDIDOS
            );
        return sf::Vector2f(
            pos_ultimo_panel.x + medidas::ANCHO_PANEL,
            medidas::FILA_BOTONES_GENERALES
        );
    }

    BotonesGenerales _crear_botones_generales( //
        const OptionalFont &font
    ) {
        const auto pos_derecha = _obtener_pos_dcha_botones_generales();
        auto botones = crear_botones_alineados_derecha(
            pos_derecha,                                           //
            datos_botones_generales,                               //
            sf::FloatRect(),                                       //
            medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES //
        );

        assert(botones.size() == 3);
        return {
            botones.at(2),
            botones.at(1),
            botones.at(0),
        };
    }

    std::shared_ptr<BotonConTexto> _crear_boton_empezar() {
        return std::make_shared<BotonConTexto>(
            boton_data_empezar,             //
            medidas::POSICION_BOTON_EMPEZAR //
        );
    }

} // namespace

///////////////////////////////////////////
// BotonesGenerales
//////////////////////////////////////////

Botones BotonesGenerales::obtener_todos() const {
    return {alternar_grid, reiniciar, salir};
}
void BotonesGenerales::alinear() {
    // TODO: eliminar duplicacion con otro metodo
    const auto pos_derecha = _obtener_pos_dcha_botones_generales();
    const auto separacion =
        medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES;
    alinear_botones_derecha(
        {alternar_grid, reiniciar, salir}, pos_derecha, separacion
    );
}

///////////////////////////////////////////
// BotonesApp
//////////////////////////////////////////

/* Establece la variable miembro 'todos', que agrupa todos los botones */
void BotonesApp::_establecer_todos() {
    todos = {empezar};
    const int num_fijos = todos.size();
    for (auto boton : generales.obtener_todos()) {
        todos.push_back(boton);
    }
    for (auto [_, boton] : despachar) {
        LOG(info) << "Anadiendo boton despachar con id " << boton->get_id()
                  << std::endl;
        todos.push_back(boton);
    }
    for (auto [_, boton] : encargar) {
        LOG(info) << "Anadiendo boton encargar con id " << boton->get_id()
                  << std::endl;
        todos.push_back(boton);
    }
}

/* Crea todos los botones */
BotonesApp::BotonesApp(
    const OptionalFont &font, const dominio::TiposDePizza &tp_disponibles,
    TipoPizzaToBoton &botones_encargar
)
    : empezar(_crear_boton_empezar()),
      generales(_crear_botones_generales(font)),
      despachar(_crear_botones_despachar(font, tp_disponibles)),
      encargar(botones_encargar) {
    _establecer_todos();
    for (auto btn : todos) {
        add_child(btn);
    }
}

void BotonesApp::set_font(const OptionalFont &new_font) {
    ComponenteConFont::set_font(new_font);
    generales.alinear();
}

void BotonesApp::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    for (auto boton_ptr : todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->actualizar();
        target.draw(*boton_ptr);
    }
}

void BotonesApp::mostrar_botones_nivel(bool nuevo_valor) {
    // TODO:ver quien es el responsable de activar los botones encargar, si
    // BotoneApp o su panel
    for (auto &[_, boton] : despachar) {
        boton->visible = nuevo_valor;
    }
    for (auto &[_, boton] : encargar) {
        boton->visible = nuevo_valor;
    }
}
