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
    sf::Text crear_etiqueta_instrucciones_o_resultado(const EstiloTexto &estilo
    ) const {
        const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
        return crearEtiqueta(estilo, font, posicion);
    }

  public:
    FabricaEtiquetasInfo(const sf::Font &font) : font(font) {}
    sf::Text generar_etiqueta_instrucciones(
        const std::string &plantilla, //
        const NumNivel &num_nivel,    //
        int objetivo                  //
    ) const {
        const auto estilo = estilos::INSTRUCCIONES;
        auto etiqueta = crear_etiqueta_instrucciones_o_resultado(estilo);
        const auto texto =
            construir_instrucciones(plantilla, num_nivel, objetivo);
        etiqueta.setString(texto);
        return etiqueta;
    }

    sf::Text generar_etiqueta_resultado() const {
        const auto estilo = estilos::RESULTADO;
        auto etiqueta = crear_etiqueta_instrucciones_o_resultado(estilo);
        etiqueta.setString(construir_resultado());
        return etiqueta;
    }
};

///////////////////////////////////////////
// EtiquetasInfo
//////////////////////////////////////////

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
