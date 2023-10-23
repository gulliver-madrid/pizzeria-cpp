#pragma once

#include "etiquetas_barra_estado.h"
#include "../../tiempo.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
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
void EtiquetasBarraEstado::actualizar(
    const Tiempo &tiempo_real, const TiempoJuego &tiempo_juego
) {
    CadenaJuego cadena(
        "Tiempo Juego: {tiempo_juego}       Tiempo Real: {tiempo_real}"
    );
    const auto tiempo_juego_str = tiempo_juego.to_string();
    const auto tiempo_real_str = tiempo_real.to_string();
    const std::string str =
        cadena.interpolar_por_clave("tiempo_juego", tiempo_juego_str)
            .interpolar_por_clave("tiempo_real", tiempo_real_str);
    etiqueta.setString(str);

    // TODO:  implementar
}
void EtiquetasBarraEstado::dibujar(sf::RenderWindow &ventana) const {
    ventana.draw(etiqueta);
}
