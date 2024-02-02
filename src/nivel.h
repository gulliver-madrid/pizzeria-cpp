#pragma once

#include "shared/num_nivel.h"
#include <memory>

class Globales;
class Grid;
class MotorNivel;
struct DatosNivel;
enum class AccionGeneral;

struct Nivel {
    std::shared_ptr<MotorNivel> motor_nivel;

    Nivel(
        std::shared_ptr<Globales> globales = nullptr,          //
        std::shared_ptr<DatosNivel> datos_nivel = nullptr,     //
        const NumNivelOpcional num_nivel = NumNivelOpcional(), //
        std::shared_ptr<Grid> grid = nullptr                   //
    );

    AccionGeneral ejecutar();
};
