#include "botones_app.h"
#include "../modelo/dominio.h"
#include "basicos_vista.h"
#include "componentes/botones.h"
#include "componentes/varios.h"
#include <cassert>

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

const std::vector<BotonConTexto *> BotonesGenerales::obtener_todos() {
    return {&alternar_grid, &reiniciar, &salir};
}

namespace {

    const std::vector<BotonData> datos_botones_generales = {
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

    /**
     * Crea y posiciona los botones asociados con la acción "encargar".
     * @param font: Fuente a utilizar para el texto del botón.
     * @param tp_disponibles: Tipos de pizza disponibles para encargar.
     * @return TipoPizzaToBoton: Un mapa que asocia cada TipoPizza con un
     * BotonConTexto.
     */
    TipoPizzaToBoton _crear_botones_encargar(
        const sf::Font &font,                      //
        const dominio::TiposDePizza &tp_disponibles //
    ) {
        // Constantes para definir la posicion de cada boton
        const sf::Vector2f pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_ENCARGAR
        );
        const auto pos_inicial_relativa_al_panel = sf::Vector2f(
            medidas::MARGEN_IZQ_ETIQUETAS, medidas::FILA_CONTENIDO_PANEL
        );
        const sf::Vector2f pos_inicial =
            pos_panel + pos_inicial_relativa_al_panel;

        // Lambda para crear boton data
        const auto crear_boton_data = [](dominio::TipoPizza tp) {
            const std::string pizza_str = tipo_pizza_to_string.at(tp);
            return BotonData{
                pizza_str,                        //
                colores::botones_encargar::FONDO, //
                colores::botones_encargar::TEXTO  //
            };
        };
        // Crea los botones
        TipoPizzaToBoton botones;
        std::vector<BotonConTexto *> ordenados;
        for (auto tp : tp_disponibles) {
            const BotonData boton_data = crear_boton_data(tp);
            botones.emplace(tp, BotonConTexto(boton_data, font));
            ordenados.push_back(&botones.at(tp));
        }

        // Posiciona los botones
        const int dif_vertical = medidas::DIF_VERTICAL_BOTONES_ENCARGAR;
        colocar_botones_en_vertical(ordenados, pos_inicial, dif_vertical);
        return botones;
    }

    TipoPizzaToBoton _crear_botones_despachar(
        const sf::Font &font,                      //
        const dominio::TiposDePizza &tp_disponibles //
    ) {
        TipoPizzaToBoton botones;
        const double escala_botones = 0.7;
        const int dif_vertical = 50;

        // Determinacion posicion inicial
        const auto pos_panel = basicos_vista::obtener_posicion_panel( //
            IndicePanel::PANEL_PREPARADAS
        );
        const auto pos_inicial_relativa_al_panel = sf::Vector2f(
            medidas::MARGEN_IZQ_ETIQUETAS + (medidas::ANCHO_PANEL * 0.55),
            medidas::FILA_CONTENIDO_PANEL
        );
        const auto pos_inicial = pos_panel + pos_inicial_relativa_al_panel;

        // Crea los botones
        std::vector<BotonConTexto *> ordenados;
        for (auto tp : tp_disponibles) {
            botones.emplace(
                tp, //
                BotonConTexto(
                    boton_data_botones_despachar, font, escala_botones
                )
            );
            ordenados.push_back(&botones.at(tp));
        }

        // Posiciona los botones
        colocar_botones_en_vertical(ordenados, pos_inicial, dif_vertical);
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
        const sf::Font &font
    ) {
        const auto pos_derecha = _obtener_pos_dcha_botones_generales();

        auto vect_botones = crear_botones_alineados_derecha(
            pos_derecha,                                           //
            datos_botones_generales,                               //
            font,                                                  //
            medidas::SEPARACION_HORIZONTAL_ENTRE_BOTONES_GENERALES //
        );

        assert(vect_botones.size() == 3);
        return {
            std::move(vect_botones.at(2)),
            std::move(vect_botones.at(1)),
            std::move(vect_botones.at(0)),
        };
    }

    BotonConTexto _crear_boton_empezar(const sf::Font &font) {
        return BotonConTexto(
            boton_data_empezar, medidas::POSICION_BOTON_EMPEZAR, font
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
    const sf::Font &font, const dominio::TiposDePizza &tp_disponibles
)
    : empezar(_crear_boton_empezar(font)),
      generales(_crear_botones_generales(font)),
      encargar(_crear_botones_encargar(font, tp_disponibles)),
      despachar(_crear_botones_despachar(font, tp_disponibles)) {
    _establecer_todos();
}

void BotonesApp::dibujar(sf::RenderWindow &ventana) const {
    for (auto boton_ptr : todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->dibujar(ventana);
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
