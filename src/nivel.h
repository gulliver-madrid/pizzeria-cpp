#pragma once

#include "general.h"
#include "globales.h"
#include "shared.h"
#include "vista/grid.h"

struct Globales;
struct BotonesApp;
struct Estado;
struct Vista;

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

struct Nivel {
  private:
    std::optional<FaseNivel> procesarEvento(
        sf::Event,          //
        const BotonesApp &, //
        Estado &            //
    );
    void procesa_cambio_de_fase(
        FaseNivel nueva_fase,                   //
        Vista &vista,                           //
        Timer &timer_espera_antes_de_resultado, //
        FaseNivel fase_previa                   //
    );
    std::optional<FaseNivel> procesa_click(
        const BotonesApp &,           //
        Estado &,                     //
        const sf::Vector2i &mouse_pos //
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
