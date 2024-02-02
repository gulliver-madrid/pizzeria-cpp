#pragma once

#include "etiquetas_barra_estado.h"
#include "../../tiempo.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
#include "../componentes/crear_etiqueta.h"
#include "../componentes/etiqueta.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

EtiquetasBarraEstado::EtiquetasBarraEstado() {
    const EstiloTexto estilo = {
        medidas::TAMANO_TEXTO_GRANDE, sf::Color::Yellow
    };
    const sf::Vector2f posicion = {
        medidas::MARGEN_IZQ_PANELES, medidas::FILA_BARRA_ESTADO
    };
    etiqueta = crear_etiqueta("", estilo, posicion, "etiqueta barra estado");
    add_child(etiqueta);
}

void EtiquetasBarraEstado::actualizar(const VistaBarraEstado &info_barra_estado
) {
    etiqueta->actualizar_texto(info_barra_estado.texto);
}

void EtiquetasBarraEstado::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    target.draw(*etiqueta);
}
