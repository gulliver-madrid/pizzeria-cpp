#pragma once

#include "comandos.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>

struct BotonConTexto;
struct BotonesApp;
struct Estado;
struct Globales;
class RealizadorBase;
enum class FaseNivel;

struct ControladorClicks {
  private:
    std::optional<Comando> genera_comando(
        const std::function<bool(const BotonConTexto &boton)> &pulsado, //
        const BotonesApp &,                                             //
        const FaseNivel fase_actual                                     //
    );

  public:
    std::optional<Comando> procesa_click(
        Globales &,                   //
        const BotonesApp &,           //
        const Estado &,               //
        const sf::Vector2i &mouse_pos //
    );
};
