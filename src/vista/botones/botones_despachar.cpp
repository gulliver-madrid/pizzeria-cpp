#include "botones_despachar.h"
#include "../../modelo/dominio.h"
#include "../../templates/helpers.h"
#include "../basicos_vista.h"
#include "../componentes/boton_con_texto.h"
#include "../componentes/botones.h"
#include "datos_botones.h"
#include <cassert>
#include <vector>

const BotonData boton_data_botones_despachar{
    "Despachar", colores::botones_despachar::FONDO,
    colores::botones_despachar::TEXTO
};

TipoPizzaToBoton
crear_botones_despachar(const dominio::TiposDePizza &tp_disponibles //
) {
    TipoPizzaToBoton botones;
    const auto escala = 0.7f;
    const float dif_vertical = 50;
    const float pequeno_ajuste = (-5);

    const auto rect_panel = basicos_vista::obtener_rect_panel( //
        IndicePanel::PANEL_PREPARADAS
    );

    const auto pos_inicial_relativa_al_panel = PosicionRelativa{sf::Vector2f(
        medidas::MARGEN_IZQ_ETIQUETAS + (medidas::ANCHO_PANEL * 0.55f),
        (medidas::FILA_CONTENIDO_PANEL + pequeno_ajuste)
    )};

    // Crea los botones
    std::vector<std::shared_ptr<BotonConTexto>> ordenados;
    for (auto tp : tp_disponibles) {
        auto boton = std::make_shared<BotonConTexto>(
            boton_data_botones_despachar, escala
        );
        botones.insert(std::make_pair(tp, boton));
        assert(has_key(botones, tp));
        ordenados.push_back(botones.at(tp));
    }

    // Posiciona los botones
    colocar_botones_en_vertical(
        ordenados, pos_inicial_relativa_al_panel, dif_vertical, rect_panel
    );
    return botones;
}
