#pragma once

#include "../general.h"
#include <optional>

class Comando;
class RealizadorBase;

namespace aplicador {
    /*
    Aplica un comando y devuelve la nueva
    fase, si correspondiera cambiar
    */
    std::optional<FaseNivel> aplicar_comando( //
        RealizadorBase &realizador,           //
        const Comando &comando                //
    );
} // namespace aplicador
