#include "botones_app.h"
#include "../../modelo/dominio.h"
#include "../../shared/log_init.h"
#include "../../templates/helpers.h"
#include "../basicos_vista.h"
#include "../componentes/boton_con_texto.h"
#include "../componentes/botones.h"
#include "../componentes/crear_etiqueta.h"
#include "datos_botones.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <cassert>
#include <iterator> // para back_inserter
#include <memory>

using std::vector;

namespace {

    const BotonData boton_data_empezar{
        "Empezar", sf::Color::Green, sf::Color::Black
    };

    std::shared_ptr<BotonConTexto> _crear_boton_empezar() {
        return std::make_shared<BotonConTexto>(
            boton_data_empezar,                               //
            PosicionRelativa{medidas::POSICION_BOTON_EMPEZAR} //
        );
    }

} // namespace

///////////////////////////////////////////
// BotonesApp
//////////////////////////////////////////

/* Establece la variable miembro 'todos', que agrupa todos los botones */
void BotonesApp::_establecer_todos() {
    todos = {empezar};
    const auto num_fijos = todos.size();
    for (auto boton : generales.obtener_todos()) {
        todos.push_back(boton);
    }
    for (auto [_, boton] : despachar) {
        LOG(info) << "Anadiendo boton despachar con id " << boton->get_id();
        todos.push_back(boton);
    }
}

/* Crea todos los botones */
BotonesApp::BotonesApp(
    const dominio::TiposDePizza &tp_disponibles, //
    TipoPizzaToBoton &botones_encargar,          //
    TipoPizzaToBoton &botones_despachar          //
)
    : empezar(_crear_boton_empezar()), generales(crear_botones_generales()),
      encargar(botones_encargar), despachar(botones_despachar) {
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
    sf::RenderStates          //
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
