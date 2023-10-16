#include "fabrica_etiquetas.h"
#include "../../textos.h"
#include "../componentes/varios.h"
#include "../vista_basics.h"

namespace medidas {
    const sf::Vector2f POSICION_INSTRUCCIONES_O_RESULTADO = {200, 200};
    constexpr int TAMANO_FUENTE_INFO = 36;
    constexpr int TAMANO_FUENTE_RESULTADO = 48;
} // namespace medidas

namespace estilos {
    const EstiloTexto RESULTADO = {
        medidas::TAMANO_FUENTE_RESULTADO, colores::TEXTO_RESULTADO
    };
    const EstiloTexto INSTRUCCIONES = {
        medidas::TAMANO_FUENTE_INFO, colores::TEXTO_INSTRUCCIONES
    };
} // namespace estilos

sf::Text
_crear_etiqueta_instrucciones_o_resultado(const EstiloTextoConFuente &estilo) {
    const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
    return crearEtiqueta(estilo, posicion);
}

sf::Text FabricaEtiquetasInfo::generar_etiqueta_instrucciones(
    const sf::Font &font,         //
    const std::string &plantilla, //
    NumNivel num_nivel,           //
    int objetivo
) {
    const auto estilo = estilos::INSTRUCCIONES;
    auto etiqueta = _crear_etiqueta_instrucciones_o_resultado({estilo, font});
    const auto texto = construir_instrucciones(plantilla, num_nivel, objetivo);
    etiqueta.setString(texto);
    return etiqueta;
}

sf::Text FabricaEtiquetasInfo::generar_etiqueta_resultado(const sf::Font &font
) {
    const auto estilo = estilos::RESULTADO;
    auto etiqueta = _crear_etiqueta_instrucciones_o_resultado({estilo, font});
    etiqueta.setString(construir_resultado());
    return etiqueta;
}
