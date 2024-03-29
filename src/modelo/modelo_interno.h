#pragma once

#include "control_pizzas.h"
#include "datos_modelo_interno.h"
#include "encargos.h"

class ModeloInterno {
  public:
    std::shared_ptr<GestorTiempoControlable> gestor_tiempo_juego;
    modelo::ControlPizzas control_pizzas;
    Encargos encargos;

    ModeloInterno(
        const std::optional<DatosModeloInterno> datos_nivel = std::nullopt
    );
    /* Encarga una pizza de tipo tp */
    void anadir_encargo(dominio::TipoPizza tp);
    /* Despacha una pizza del tipo indicado. */
    bool despachar_pizza( //
        const dominio::TipoPizza tp
    );
    EstadoPreparacionPizzas obtener_estado_preparacion_pizzas() const;
    sf::Time obtener_tiempo_juego() const;
    void evaluar_preparacion_pizzas();
};
