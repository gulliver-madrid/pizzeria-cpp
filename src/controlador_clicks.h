#pragma once

#include "modelo_amplio/comandos.h"
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <optional>

enum class FaseNivel;
struct BotonConTexto;
class BotonesApp;
struct ModeloAmplio;
struct Globales;
struct RealizadorBase;

struct ControladorClicks {
  private:
    std::optional<Comando> genera_comando(
        const std::function<bool(const BotonConTexto &boton)> &pulsado, //
        const std::shared_ptr<const BotonesApp> &,                      //
        const FaseNivel fase_actual                                     //
    );

  public:
    std::optional<Comando> procesa_click(
        Globales &,                                //
        const std::shared_ptr<const BotonesApp> &, //
        const FaseNivel fase_actual,               //
        const sf::Vector2i &mouse_pos              //
    );
};
