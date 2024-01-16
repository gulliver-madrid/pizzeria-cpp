#include "botones_app.h"
#include "../modelo/dominio.h"
#include "../templates/helpers.h"
#include "basicos_vista.h"
#include "componentes/botones.h"
#include "componentes/varios.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <cassert>

using std::move;
using std::vector;

namespace colores {
    namespace botones_encargar {
        const auto FONDO = sf::Color::Green;
        const auto TEXTO = sf::Color::Black;
    } // namespace botones_encargar
    namespace botones_despachar {
        const auto FONDO = sf::Color::Green;
        const auto TEXTO = sf::Color::Black;
    } // namespace botones_despachar
} // namespace colores

namespace medidas {
    const auto POSICION_BOTON_EMPEZAR = sf::Vector2f(500, 450);
    const auto DIF_VERTICAL_BOTONES_ENCARGAR = 80;
} // namespace medidas

///////////////////////////////////////////
// BotonesGenerales
//////////////////////////////////////////

const vector<BotonConTexto *> BotonesGenerales::obtener_todos() {
    return {&alternar_grid, &reiniciar, &salir};
}

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

    vector<BotonDataConFont> anadir_fuente( //
        const vector<BotonData> &datos, const OptionalFont &font
    ) {
        vector<BotonDataConFont> result;
        transform(
            datos.begin(), datos.end(), std::back_inserter(result),
            [&font](BotonData data) -> BotonDataConFont { //
                return {data, font};
            }
        );
        return result;
    }

    /**
     * Crea y posiciona los botones asociados con la accion "encargar".
     * @param font: Fuente a utilizar para el texto del boton.
     * @param tp_disponibles: Tipos de pizza disponibles para encargar.
     * @return TipoPizzaToBoton: Un mapa que asocia cada TipoPizza con un
     * BotonConTexto.
     */
    TipoPizzaToBoton _crear_botones_encargar(
        const OptionalFont &font,                   //
        const dominio::TiposDePizza &tp_disponibles //
    ) {
        // Constantes para definir la posicion de cada boton
        const auto rect_panel = basicos_vista::obtener_rect_panel( //
            IndicePanel::PANEL_ENCARGAR
        );
        const sf::Vector2f pos_panel = rect_panel.getPosition();
        const auto pos_inicial_relativa_al_panel = sf::Vector2f(
            medidas::MARGEN_IZQ_ETIQUETAS, medidas::FILA_CONTENIDO_PANEL
        );

        // Lambda para crear boton data
        const auto crear_boton_data = [](dominio::TipoPizza tp) {
            assert(has_key(tipo_pizza_to_string, tp));
            const std::string pizza_str = tipo_pizza_to_string.at(tp);
            return BotonData{
                pizza_str,                        //
                colores::botones_encargar::FONDO, //
                colores::botones_encargar::TEXTO  //
            };
        };

        // Crea los botones
        TipoPizzaToBoton botones;
        vector<BotonConTexto *> ordenados;
        for (auto tp : tp_disponibles) {
            const BotonData boton_data = crear_boton_data(tp);
            botones.emplace(tp, BotonConTexto({boton_data, font}));
            botones.at(tp).establecer_contenedor(rect_panel);
            ordenados.push_back(&botones.at(tp));
        }

        // Posiciona los botones
        const int dif_vertical = medidas::DIF_VERTICAL_BOTONES_ENCARGAR;
        colocar_botones_en_vertical(
            ordenados, pos_inicial_relativa_al_panel, dif_vertical
        );
        return botones;
    }

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
        vector<BotonConTexto *> ordenados;
        for (auto tp : tp_disponibles) {
            botones.emplace(
                tp, //
                BotonConTexto(
                    {boton_data_botones_despachar, font}, //
                    escala                                //
                )
            );
            assert(has_key(botones, tp));
            botones.at(tp).establecer_contenedor(rect_panel);
            ordenados.push_back(&botones.at(tp));
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
        const auto datos_botones = anadir_fuente( //
            datos_botones_generales, font
        );

        auto botones = crear_botones_alineados_derecha(
            pos_derecha,                                           //
            datos_botones,                                         //
            sf::FloatRect(),                                       //
            medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES //
        );

        assert(botones.size() == 3);
        return {
            move(botones.at(2)),
            move(botones.at(1)),
            move(botones.at(0)),
        };
    }

    BotonConTexto _crear_boton_empezar(const OptionalFont &font) {
        return BotonConTexto(
            {boton_data_empezar, font},     //
            medidas::POSICION_BOTON_EMPEZAR //
        );
    }

} // namespace

///////////////////////////////////////////
// BotonesApp
//////////////////////////////////////////

/* Establece la variable miembro 'todos', que agrupa todos los botones */
void BotonesApp::_establecer_todos() {
    todos = {&empezar};
    const int num_fijos = todos.size();
    for (auto &boton : generales.obtener_todos()) {
        todos.push_back(boton);
    }
    for (auto &[_, boton] : despachar) {
        todos.push_back(&boton);
    }
    for (auto &[_, boton] : encargar) {
        todos.push_back(&boton);
    }
}

/* Crea todos los botones */
BotonesApp::BotonesApp(
    const OptionalFont &font, const dominio::TiposDePizza &tp_disponibles
)
    : empezar(_crear_boton_empezar(font)),
      generales(_crear_botones_generales(font)),
      encargar(_crear_botones_encargar(font, tp_disponibles)),
      despachar(_crear_botones_despachar(font, tp_disponibles)) {
    _establecer_todos();
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
    for (auto &[_, boton] : despachar) {
        boton.visible = nuevo_valor;
    }
    for (auto &[_, boton] : encargar) {
        boton.visible = nuevo_valor;
    }
}
