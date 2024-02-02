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

EtiquetasPreparadas::EtiquetasPreparadas(
    const dominio::TiposDePizza &tp_disponibles
) {
    LOG(debug) << "Tipos de pizza disponibles: " << tp_disponibles.size();
    FabricaEtiquetasPreparadas fabrica;
    size_t i = 0;
    for (auto tp : tp_disponibles) {
        auto etiqueta = fabrica.crearEtiquetaPizzasPreparadas(i);
        etiquetas_preparadas.emplace(tp, etiqueta);
        add_child(etiqueta);
        i++;
    }

    LOG(debug) << "etiquetas_preparadas: " << tp_disponibles.size();
}

void EtiquetasPreparadas::actualizar(const PizzasToStrings &info_preparadas) {
    for (auto &[tp, linea] : info_preparadas) {
        assert(has_key(etiquetas_preparadas, tp));
        etiquetas_preparadas.at(tp)->actualizar_texto(linea);
    }
}

void EtiquetasPreparadas::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    dibujar_elementos(target, etiquetas_preparadas);
}
