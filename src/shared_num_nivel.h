#pragma once

#include <cassert>
#include <optional>
#include <string>

/* NewType para el numero de nivel del juego */
class NumNivelOpcional {
  private:
    const std::optional<int> valor;

  public:
    NumNivelOpcional() {}
    explicit NumNivelOpcional(int v) : valor(v) { //
        assert(valor > 0);
    }
    std::string to_string() const { //
        if (!valor)
            return "-";
        return std::to_string(valor.value());
    }
    int get_valor() const { //
        return valor.value();
    }
};
