#include "botones_encargar.h"
#include "../../modelo/dominio.h"
#include "../../templates/helpers.h"
#include "../basicos_vista.h"
#include "../componentes/boton_con_texto.h"
#include "../componentes/botones.h"
#include "datos_botones.h"
#include <cassert>

using std::vector;

TipoPizzaToBoton crear_botones_encargar(        //
    const dominio::TiposDePizza &tp_disponibles //
) {
    // Constantes para definir la posicion de cada boton
    const auto rect_panel = basicos_vista::obtener_rect_panel( //
        IndicePanel::PANEL_ENCARGAR
    );
    const sf::Vector2f pos_panel = rect_panel.getPosition();
    const auto pos_inicial_relativa_al_panel = PosicionRelativa{sf::Vector2f(
        medidas::MARGEN_IZQ_ETIQUETAS, medidas::FILA_CONTENIDO_PANEL
    )};

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
    vector<std::shared_ptr<BotonConTexto>> ordenados;
    for (auto tp : tp_disponibles) {
        const BotonData boton_data = crear_boton_data(tp);
        BotonData data = {boton_data};
        botones[tp] = std::make_shared<BotonConTexto>(data);
        ordenados.push_back(botones.at(tp));
    }

    // Posiciona los botones
    const int dif_vertical = medidas::DIF_VERTICAL_BOTONES_ENCARGAR;
    colocar_botones_en_vertical(
        ordenados, pos_inicial_relativa_al_panel, dif_vertical, rect_panel
    );
    return botones;
}
