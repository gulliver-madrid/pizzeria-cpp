#pragma once

#include "control_pizzas.h"
#include "encargos.h"

struct DatosNivelParaModelo;

struct EstadoModelo {
    GestorTiempoJuego gestor_tiempo;
    modelo::ControlPizzas control_pizzas;
    Encargos encargos;

    EstadoModelo(const DatosNivelParaModelo &datos_nivel);
    /* Encarga una pizza de tipo tp */
    void anadir_encargo(dominio::TipoPizza tp);
    /* Despacha una pizza del tipo indicado. */
    bool despachar_pizza( //
        const dominio::TipoPizza tp
    );
    EstadoPreparacionPizzas obtener_estado_preparacion_pizzas() const;
    TiempoJuego obtener_tiempo_juego() const;
    void evaluar_preparacion_pizzas();
};