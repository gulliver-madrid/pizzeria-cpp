#pragma once

#include "etiquetas_barra_estado.h"
#include "../basicos_vista.h"
#include "../componentes/varios.h"

EtiquetasBarraEstado::EtiquetasBarraEstado(const sf::Font &font) : font(font) {
    const EstiloTexto estilo = {
        medidas::TAMANO_TEXTO_GRANDE, sf::Color::Yellow
    };
    etiqueta = crearEtiqueta(
        "Tiempo Juego: 00:00       Tiempo Real: 00:00", estilo, font,
        {medidas::MARGEN_IZQ_PANELES, medidas::FILA_BARRA_ESTADO}
    );
}
void EtiquetasBarraEstado::actualizar() {
    // TODO:  implementar
}
void EtiquetasBarraEstado::dibujar(sf::RenderWindow &ventana) const {
    ventana.draw(etiqueta);
}
