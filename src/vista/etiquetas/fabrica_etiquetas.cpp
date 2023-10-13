#include "fabrica_etiquetas.h"
#include "../../textos.h"
#include "../componentes/varios.h"
#include "../vista_basics.h"

namespace medidas {
    const sf::Vector2f POSICION_INSTRUCCIONES_O_RESULTADO = {200, 200};
    constexpr int TAMANO_FUENTE_INFO = 36;
    constexpr int TAMANO_FUENTE_RESULTADO = 48;
} // namespace medidas

sf::Text FabricaEtiquetasInfo::generar_etiqueta_instrucciones(
    const sf::Font &font,         //
    const std::string &plantilla, //
    NumNivel num_nivel,           //
    int objetivo
) {
    const auto color = colores::COLOR_TEXTO_INSTRUCCIONES;
    const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
    EstiloTexto estilo_texto = {medidas::TAMANO_FUENTE_INFO, color, font};
    auto etiqueta = crearEtiqueta(estilo_texto, posicion);
    const auto texto = construir_instrucciones(plantilla, num_nivel, objetivo);
    etiqueta.setString(texto);
    return etiqueta;
}

sf::Text FabricaEtiquetasInfo::generar_etiqueta_resultado(const sf::Font &font
) {
    auto etiqueta = crearEtiqueta(
        medidas::TAMANO_FUENTE_RESULTADO, font, colores::COLOR_TEXTO_RESULTADO,
        medidas::POSICION_INSTRUCCIONES_O_RESULTADO
    );
    etiqueta.setString(construir_resultado());
    return etiqueta;
}
