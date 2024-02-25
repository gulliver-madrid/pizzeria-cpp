#pragma once

#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>
#include <optional>

enum class FaseNivel;
class BotonConTexto;
class BotonesApp;
class Globales;
class Comando;

using FuncionPulsado =
    std::function<bool(const std::shared_ptr<BotonConTexto> boton)>;

class ControladorClicks {
  private:
    std::optional<Comando> genera_comando(
        const FuncionPulsado &,                    //
        const std::shared_ptr<const BotonesApp> &, //
        const FaseNivel fase_actual                //
    );

  public:
    std::optional<Comando> procesa_click(
        const std::shared_ptr<Globales>,           //
        const std::shared_ptr<const BotonesApp> &, //
        const FaseNivel fase_actual,               //
        const sf::Vector2i &mouse_pos              //
    );
};
