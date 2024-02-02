#include "barras_progreso.h"
#include "basicos_vista.h"
#include "vista_data.h"

namespace medidas {
    constexpr float DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
    namespace barra_progreso {
        constexpr float ancho = 300;
        constexpr float largo = 40;
    } // namespace barra_progreso
} // namespace medidas

namespace colores {
    static const ColoresBPN colores_bpn = {
        colores::barra_progreso::FONDO,
        colores::barra_progreso::RELLENO,
        colores::barra_progreso::TEXTO,
    };
}

namespace {
    sf::Vector2f obtener_dimensiones_barra_progreso() {
        using medidas::barra_progreso::ancho;
        using medidas::barra_progreso::largo;
        static const auto dimensiones = sf::Vector2f(ancho, largo);
        return dimensiones;
    }

    std::shared_ptr<BarraProgresoConNombre> crear_barra_progreso_con_nombre(
        const sf::Vector2f &dimensiones,                 //
        const VistaPreparacionPizza &presentacion_pizza, //
        const sf::Vector2f &posicion                     //
    ) {
        const auto bpn = std::make_shared<BarraProgresoConNombre>(
            dimensiones,                     //
            presentacion_pizza.nombre_pizza, //
            posicion,                        //
            colores::colores_bpn             //
        );
        bpn->actualizar_porcentaje(presentacion_pizza.porcentaje);
        return bpn;
    }
} // namespace

/* Crea y actualiza las barras de progreso */
std::vector<std::shared_ptr<BarraProgresoConNombre>> crear_barras_progreso(
    const PresentacionPreparacionPizzas &presentacion,
    const sf::Vector2f &pos_panel
) {
    const auto dimensiones = obtener_dimensiones_barra_progreso();
    constexpr float diferencia_vertical =
        medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;

    const auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    auto pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;

    std::vector<std::shared_ptr<BarraProgresoConNombre>> barras{};
    for (auto &presentacion_pizza : presentacion) {
        const auto posicion = sf::Vector2f(pos_x, pos_y);
        const auto bpn = crear_barra_progreso_con_nombre(
            dimensiones, presentacion_pizza, posicion
        );
        barras.push_back(bpn);
        pos_y += diferencia_vertical;
    }

    return barras;
}
