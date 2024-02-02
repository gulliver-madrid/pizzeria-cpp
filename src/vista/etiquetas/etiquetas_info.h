#pragma once

#include "../../shared/font.h"
#include "../../shared/num_nivel.h"
#include "../componentes/componente.h"
#include "../presentacion_vista.h"
#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include <optional>

class Etiqueta;

class EtiquetasInfo : public ComponenteConFont {
  private:
    std::shared_ptr<PresentacionVista> presentacion_vista;

  public:
    std::shared_ptr<Etiqueta> instrucciones;
    std::shared_ptr<Etiqueta> resultado;

    EtiquetasInfo();
    void setup(
        const std::string &instr, //
        const NumNivelOpcional &  //

    );
    void set_presentacion_vista(
        std::shared_ptr<PresentacionVista> presentacion_vista //
    );
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
