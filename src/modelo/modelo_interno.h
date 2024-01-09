#pragma once

#include "control_pizzas.h"
#include "encargos.h"

struct DatosModeloInterno;

struct ModeloInterno {
    GestorTiempoJuego gestor_tiempo;
    modelo::ControlPizzas control_pizzas;
    Encargos encargos;

    ModeloInterno(const DatosModeloInterno &datos_nivel);
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
