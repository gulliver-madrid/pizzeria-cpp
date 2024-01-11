#pragma once

#include "../fase_nivel.h"
#include "../modelo/datos_modelo_interno.h"
#include "../modelo/modelo_interno.h"

class ObservadorFase;
class Comando;

class ModeloAmplio {
  private:
    FaseNivel fase_actual = FaseNivel::None;

  public:
    std::vector<std::reference_wrapper<ObservadorFase>> observadores_fase;
    ModeloInterno modelo_interno;

    bool establecido = false;
    bool mostrando_grid = false;

    ModeloAmplio::ModeloAmplio(const DatosModeloInterno &datos_modelo_interno);

    void set_fase_actual(FaseNivel);
    FaseNivel get_fase_actual() const;
};
