#pragma once

#include "../fase_nivel.h"
#include "../modelo/datos_modelo_interno.h"
#include "../modelo/modelo_interno.h"
#include <memory>

class ObservadorFase;
class Comando;

class ModeloAmplio {
  private:
    FaseNivel fase_actual = FaseNivel::None;

  public:
    std::vector<std::shared_ptr<ObservadorFase>> observadores_fase;
    ModeloInterno modelo_interno;
    GestorTiempoGeneral gestor_tiempo_general;

    bool establecido = false;
    bool mostrando_grid = false;

    ModeloAmplio(
        const std::optional<DatosModeloInterno> datos_modelo_interno =
            std::nullopt
    );

    void set_fase_actual(FaseNivel);
    FaseNivel get_fase_actual() const;
};
