#include "etiquetas_info.h"
#include "../../shared/log_init.h"
#include "../../textos.h"
#include "../basicos_vista.h"
#include "../componentes/etiqueta.h"
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
    std::shared_ptr<Etiqueta> crear_etiqueta_info(
        const std::string &texto, const EstiloTexto &estilo
    ) const {
        const auto posicion = medidas::POSICION_INSTRUCCIONES_O_RESULTADO;
        return crear_etiqueta(texto, estilo, font, posicion);
    }

  public:
    FabricaEtiquetasInfo(const OptionalFont &font) : ObjetoConFont(font) {}
    std::shared_ptr<Etiqueta> crear_etiqueta_instrucciones(
        const std::string &plantilla,     //
        const NumNivelOpcional &num_nivel //
    ) const {
        const auto estilo = estilos::INSTRUCCIONES;
        const auto texto = construir_texto_instrucciones(plantilla, num_nivel);
        LOG(info) << "Instrucciones construidas" << std::endl;
        const auto etiqueta = crear_etiqueta_info(texto, estilo);
        return etiqueta;
    }

    std::shared_ptr<Etiqueta> crear_etiqueta_resultado() const {
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
    const std::string &instr,         //
    const NumNivelOpcional &num_nivel //
) {
    const auto fabrica = FabricaEtiquetasInfo(font);
    LOG(info) << "Construyendo instrucciones" << std::endl;
    instrucciones = fabrica.crear_etiqueta_instrucciones(instr, num_nivel);
    LOG(info) << "Construyendo etiqueta resultado" << std::endl;
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
        target.draw(*instrucciones);
    }
    if (presentacion_vista->visibilidad.resultado) {
        target.draw(*resultado);
    }
}
