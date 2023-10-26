#pragma once

#include "general.h"
#include "globales.h"
#include "shared.h"
#include "vista/grid.h"

struct BotonesApp;
struct EnlaceVista;
struct Estado;
struct Globales;

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

struct Nivel {
  private:
    std::optional<FaseNivel> procesarEvento(
        sf::Event,          //
        const BotonesApp &, //
        Estado &            //
    );
    std::optional<AccionGeneral> procesa_cambio_de_fase(
        FaseNivel nueva_fase,                   //
        const EnlaceVista &enlace_vista,        //
        Timer &timer_espera_antes_de_resultado, //
        FaseNivel fase_previa                   //
    );
    std::optional<FaseNivel> procesa_click(
        const BotonesApp &,           //
        Estado &,                     //
        const sf::Vector2i &mouse_pos //
    );
    EnlaceVista crear_enlace_vista(
        const modelo::ControlPizzas &control_pizzas, //
        std::optional<int> objetivo_estatico         //
    );

  public:
    Globales &globales;
    const DatosNivel &datos_nivel;
    const NumNivel &num_nivel;
    Grid &grid;
    const bool es_el_ultimo;

    Nivel(
        Globales &,         //
        const DatosNivel &, //
        const NumNivel &,   //
        Grid &,             //
        bool es_el_ultimo   //
    );
    AccionGeneral ejecutar();
};
