#include "etiquetas_info.h"
#include "../../textos.h"
#include "../basicos_vista.h"
#include "../componentes/varios.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <memory>

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

struct FabricaEtiquetasInfo : public ObjetoConFont {
  private:
    sf::Text crear_etiqueta_info(
        const std::string &texto, const EstiloTexto &estilo
    ) const {
        const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
        return crearEtiqueta(texto, estilo, font, posicion);
    }

  public:
    FabricaEtiquetasInfo(const OptionalFont &font) : ObjetoConFont(font) {}
    sf::Text crear_etiqueta_instrucciones(
        const std::string &plantilla,             //
        const std::shared_ptr<NumNivel> num_nivel //
    ) const {
        std::cout << "en crear_etiqueta_instrucciones" << std::endl;
        const auto estilo = estilos::INSTRUCCIONES;
        const auto texto = construir_texto_instrucciones(plantilla, num_nivel);
        std::cout << "Instrucciones construidas" << std::endl;
        const auto etiqueta = crear_etiqueta_info(texto, estilo);
        return etiqueta;
    }

    sf::Text crear_etiqueta_resultado() const {
        const auto estilo = estilos::RESULTADO;
        const auto texto = construir_resultado();
        const auto etiqueta = crear_etiqueta_info(texto, estilo);
        return etiqueta;
    }
};

///////////////////////////////////////////
// EtiquetasInfo
//////////////////////////////////////////

EtiquetasInfo::EtiquetasInfo(const OptionalFont &font) : ObjetoConFont(font) {}

void EtiquetasInfo::setup(
    const std::string &instr,                 //
    const std::shared_ptr<NumNivel> num_nivel //
) {
    const auto fabrica = FabricaEtiquetasInfo(font);
    std::cout << "Construyendo instrucciones" << std::endl;
    instrucciones = fabrica.crear_etiqueta_instrucciones(instr, num_nivel);
    std::cout << "Construyendo etiqueta resultado" << std::endl;
    resultado = fabrica.crear_etiqueta_resultado();
}

void EtiquetasInfo::set_presentacion_vista(
    std::shared_ptr<PresentacionVista> presentacion_vista //
) {
    this->presentacion_vista = presentacion_vista;
}

void EtiquetasInfo::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    if (presentacion_vista->visibilidad.instrucciones) {
        target.draw(instrucciones);
    }
    if (presentacion_vista->visibilidad.resultado) {
        target.draw(resultado);
    }
}
