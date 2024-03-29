#pragma once

#include <optional>

enum class FaseNivel;
class Comando;
class ModeloAmplio;
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

std::optional<FaseNivel> aplica_comando_a_modelo(
    ModeloAmplio &, //
    const Comando & //
);
