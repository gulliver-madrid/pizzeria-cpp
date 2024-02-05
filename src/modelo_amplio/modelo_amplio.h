#pragma once

#include "../fase_nivel.h"
#include "../modelo/datos_modelo_interno.h"
#include "../modelo/modelo_interno.h"
#include <memory>

class ObservadorFase;
class Comando;

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = sf::seconds(2.5);
    const auto ESPERA_ENTRE_NIVELES = sf::seconds(3);
} // namespace tiempos

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
    sf::Time obtener_tiempo_transcurrido() const;
    void activar_tiempo_juego();
    void iniciar_espera_antes_resultado();
    void iniciar_espera_entre_niveles();
    bool termino_timer(GestorTiempoKey) const;
};
