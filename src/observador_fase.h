#pragma once

enum class FaseNivel;

class ObservadorFase {
  public:
    virtual void on_cambio_de_fase(FaseNivel) = 0;
};
