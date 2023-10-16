#include "fabrica_etiquetas.h"
#include "../../textos.h"
#include "../componentes/varios.h"
#include "../vista_basics.h"

namespace medidas {
    const sf::Vector2f POSICION_INSTRUCCIONES_O_RESULTADO = {200, 200};
    constexpr int TAMANO_FUENTE_INFO = 36;
    constexpr int TAMANO_FUENTE_RESULTADO = 48;
} // namespace medidas

sf::Text _crear_etiqueta_instrucciones_o_resultado(const EstiloTexto &estilo) {
    const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
    return crearEtiqueta(estilo, posicion);
}

sf::Text FabricaEtiquetasInfo::generar_etiqueta_instrucciones(
    const sf::Font &font,         //
    const std::string &plantilla, //
    NumNivel num_nivel,           //
    int objetivo
) {
    const auto tamano_fuente = medidas::TAMANO_FUENTE_INFO;
    const auto color = colores::COLOR_TEXTO_INSTRUCCIONES;
    const auto estilo = EstiloTexto{tamano_fuente, color, font};
    auto etiqueta = _crear_etiqueta_instrucciones_o_resultado(estilo);
    const auto texto = construir_instrucciones(plantilla, num_nivel, objetivo);
    etiqueta.setString(texto);
    return etiqueta;
}

sf::Text FabricaEtiquetasInfo::generar_etiqueta_resultado(const sf::Font &font
) {
    const auto tamano_fuente = medidas::TAMANO_FUENTE_RESULTADO;
    const auto color = colores::COLOR_TEXTO_RESULTADO;
    const auto estilo = EstiloTexto{tamano_fuente, color, font};
    auto etiqueta = _crear_etiqueta_instrucciones_o_resultado(estilo);
    etiqueta.setString(construir_resultado());
    return etiqueta;
}
