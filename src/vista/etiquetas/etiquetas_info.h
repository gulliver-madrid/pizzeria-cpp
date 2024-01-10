#pragma once

#include "../../shared.h"
#include <SFML/Graphics/Text.hpp>
#include <optional>

struct VisibilidadEtiquetasInfo {
    bool mostrar_instrucciones;
    bool mostrar_resultado;
};

struct EtiquetasInfo : public ObjetoConFont, public sf::Drawable {
  private:
    VisibilidadEtiquetasInfo &visibilidad;

  public:
    sf::Text instrucciones;
    sf::Text resultado;

    EtiquetasInfo(const sf::Font &);
    void setup(
        const std::string &instr, //
        const NumNivel &          //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
    void set_clean();
};
