#pragma once

#include "etiquetas_barra_estado.h"
#include "../basicos_vista.h"
#include "../componentes/varios.h"

EtiquetasBarraEstado::EtiquetasBarraEstado(const sf::Font &font) : font(font) {
    const EstiloTexto estilo = {24, sf::Color::Green};
    etiqueta = crearEtiqueta(
        "EtiquetasBarraEstado", estilo, font, {0, medidas::FILA_BARRA_ESTADO}
    );
}
void EtiquetasBarraEstado::actualizar() {
    // TODO:  implementar
}
void EtiquetasBarraEstado::dibujar(sf::RenderWindow &ventana) const {
    ventana.draw(etiqueta);
}
