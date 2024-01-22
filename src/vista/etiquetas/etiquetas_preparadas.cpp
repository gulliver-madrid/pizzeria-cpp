#include "etiquetas_preparadas.h"
#include "../../modelo/dominio.h"
#include "../../shared/log_init.h"
#include "../../templates/dibujar_elementos.h"
#include "../../templates/helpers.h"
#include "../componentes/etiqueta.h"
#include "fabrica_etiquetas_preparadas.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>
#include <iostream>

///////////////////////////////////////////
// EtiquetasPreparadas (public)
//////////////////////////////////////////

EtiquetasPreparadas::EtiquetasPreparadas() {}

void EtiquetasPreparadas::setup(const dominio::TiposDePizza &tp_disponibles) {
    LOG(debug) << "Tipos de pizza disponibles: " << tp_disponibles.size();
    FabricaEtiquetasPreparadas fabrica(font);
    int i = 0;
    for (auto tp : tp_disponibles) {
        auto etiqueta = fabrica.crearEtiquetaPizzasPreparadas(i);
        etiquetas_preparadas.emplace(tp, etiqueta);
        add_child(etiqueta);
        i++;
    }

    LOG(debug) << "etiquetas_preparadas: " << tp_disponibles.size();
};

void EtiquetasPreparadas::actualizar(const PizzasToStrings &vista_preparadas) {
    for (auto &[tp, linea] : vista_preparadas) {
        assert(has_key(etiquetas_preparadas, tp));
        etiquetas_preparadas.at(tp)->actualizar_texto(linea);
    }
}

void EtiquetasPreparadas::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    dibujar_elementos(target, etiquetas_preparadas);
}
