#pragma once

#include <optional>
#include <string>

/* NewType para el numero de nivel del juego */
class NumNivel {
  private:
    const int valor;

  public:
    explicit NumNivel(int v);
    std::string to_string() const;
    int get_valor() const;
};

using NumNivelOpcional = std::optional<NumNivel>;

std::string to_string(NumNivelOpcional opt_num_nivel);
