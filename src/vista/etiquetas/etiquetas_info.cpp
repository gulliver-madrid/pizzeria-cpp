#include "etiquetas_info.h"
#include "../../textos.h"
#include "../basicos_vista.h"
#include "../componentes/varios.h"

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

///////////////////////////////////////////
// FabricaEtiquetasInfo
//////////////////////////////////////////

struct FabricaEtiquetasInfo {
  private:
    const sf::Font &font;
    sf::Text crear_etiqueta_instrucciones_o_resultado(
        const std::string &texto, const EstiloTexto &estilo
    ) const {
        const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
        return crearEtiqueta(texto, estilo, font, posicion);
    }

  public:
    FabricaEtiquetasInfo(const sf::Font &font) : font(font) {}
    sf::Text generar_etiqueta_instrucciones(
        const std::string &plantilla, //
        const NumNivel &num_nivel,    //
        int objetivo                  //
    ) const {
        const auto estilo = estilos::INSTRUCCIONES;
        const auto texto =
            construir_instrucciones(plantilla, num_nivel, objetivo);
        const auto etiqueta =
            crear_etiqueta_instrucciones_o_resultado(texto, estilo);
        return etiqueta;
    }

    sf::Text generar_etiqueta_resultado() const {
        const auto estilo = estilos::RESULTADO;
        const auto texto = construir_resultado();
        const auto etiqueta =
            crear_etiqueta_instrucciones_o_resultado(texto, estilo);
        return etiqueta;
    }
};

///////////////////////////////////////////
// EtiquetasInfo
//////////////////////////////////////////

EtiquetasInfo::EtiquetasInfo(const sf::Font &font) : font(font) {}

void EtiquetasInfo::setup(
    const std::string &instr,  //
    const NumNivel &num_nivel, //
    int total_objetivos        //
) {
    const auto fabrica = FabricaEtiquetasInfo(font);
    instrucciones = fabrica.generar_etiqueta_instrucciones(
        instr, num_nivel, total_objetivos
    );
    resultado = fabrica.generar_etiqueta_resultado();
}
