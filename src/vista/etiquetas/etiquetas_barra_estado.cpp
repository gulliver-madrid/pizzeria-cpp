#pragma once

#include "etiquetas_barra_estado.h"
#include "../../tiempo.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
#include "../componentes/etiqueta.h"
#include "../componentes/varios.h"
#include "../presentador.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

const auto crear_texto = presentador::crea_texto_etiqueta_barra_estado;

EtiquetasBarraEstado::EtiquetasBarraEstado(const OptionalFont &font)
    : ObjetoConFont(font) {
    const EstiloTexto estilo = {
        medidas::TAMANO_TEXTO_GRANDE, sf::Color::Yellow
    };
    const auto texto_inicial = crear_texto(sf::Time::Zero, sf::Time::Zero);
    const sf::Vector2f posicion = {
        medidas::MARGEN_IZQ_PANELES, medidas::FILA_BARRA_ESTADO
    };
    etiqueta = crear_puntero_a_etiqueta(texto_inicial, estilo, font, posicion);
}

void EtiquetasBarraEstado::actualizar(
    const sf::Time &tiempo_real, const sf::Time &tiempo_juego
) {
    const auto texto = crear_texto(tiempo_real, tiempo_juego);
    etiqueta->setString(texto);
}

void EtiquetasBarraEstado::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    target.draw(*etiqueta);
}
