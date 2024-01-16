#pragma once

#include "../../shared.h"
#include "../../shared_num_nivel.h"
#include "../presentacion_vista.h"
#include <SFML/Graphics/Text.hpp>
#include <optional>

struct EtiquetasInfo : public ObjetoConFont, public sf::Drawable {
  private:
    std::shared_ptr<PresentacionVista> presentacion_vista;

  public:
    sf::Text instrucciones;
    sf::Text resultado;

    EtiquetasInfo(const OptionalFont &);
    void setup(
        const std::string &instr, //
        const NumNivelOpcional &  //

    );
    void set_presentacion_vista(
        std::shared_ptr<PresentacionVista> presentacion_vista //
    );
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
