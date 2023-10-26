#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>

struct BotonConTexto;
struct BotonesApp;
struct Estado;
struct Globales;
class RealizadorBase;
class Comando;
enum class FaseNivel;

struct ControladorClicks {
  private:
    std::optional<Comando> genera_comando(
        const std::function<bool(const BotonConTexto &boton)> &pulsado, //
        const BotonesApp &,                                             //
        const FaseNivel fase_actual                                     //
    );
    std::optional<FaseNivel> aplica_comando(
        RealizadorBase &, //
        const Comando &   //
    );

  public:
    std::optional<FaseNivel> procesa_click(
        Globales &,                   //
        const BotonesApp &,           //
        const Estado &,               //
        RealizadorBase &,             //
        const sf::Vector2i &mouse_pos //
    );
};
