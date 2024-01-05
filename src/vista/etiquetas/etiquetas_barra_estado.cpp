#pragma once

#include "etiquetas_barra_estado.h"
#include "../../tiempo.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
#include "../componentes/varios.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

EtiquetasBarraEstado::EtiquetasBarraEstado(const sf::Font &font)
    : ObjetoConFont(font) {
    const EstiloTexto estilo = {
        medidas::TAMANO_TEXTO_GRANDE, sf::Color::Yellow
    };
    etiqueta = crearEtiqueta(
        "Tiempo Juego: 00:00       Tiempo Real: 00:00", estilo, font,
        {medidas::MARGEN_IZQ_PANELES, medidas::FILA_BARRA_ESTADO}
    );
}

void EtiquetasBarraEstado::actualizar(
    const sf::Time &tiempo_real, const sf::Time &tiempo_juego
) {
    CadenaJuego cadena(
        "Tiempo Juego: {tiempo_juego}       Tiempo Real: {tiempo_real}"
    );
    const std::string str =
        cadena
            .interpolar_por_clave("tiempo_juego", time_to_string(tiempo_juego))
            .interpolar_por_clave("tiempo_real", time_to_string(tiempo_real));
    etiqueta.setString(str);
}

void EtiquetasBarraEstado::dibujar(sf::RenderTarget &target) const {
    target.draw(etiqueta);
}
