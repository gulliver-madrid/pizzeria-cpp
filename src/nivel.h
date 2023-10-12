#pragma once

#include "general.h"
#include "globales.h"
#include "shared.h"
#include "vista/grid.h"

struct Globales;
struct Botones;
struct Estado;

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

struct Nivel {
  private:
    std::optional<FaseNivel> procesarEvento(
        sf::Event evento,       //
        const Botones &botones, //
        Estado &estado          //
    );

  public:
    Globales &globales;
    const DatosNivel &datos_nivel;
    NumNivel num_nivel;
    Grid &grid;
    bool es_el_ultimo;

    Nivel(
        Globales &globales, const DatosNivel &datos_nivel, NumNivel num_nivel,
        Grid &grid, bool es_el_ultimo
    );
    AccionGeneral ejecutar();
};
