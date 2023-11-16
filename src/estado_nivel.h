#pragma once

#include "modelo/control_pizzas.h"
#include "modelo/encargos.h"

enum class FaseNivel;
struct DatosNivel;

struct EstadoModelo {
    GestorTiempoJuego gestor_tiempo;
    modelo::ControlPizzas control_pizzas;
    Encargos encargos;

    EstadoModelo(const DatosNivel &datos_nivel);
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

/* Estado mutable de un nivel */
struct Estado {
    FaseNivel fase_actual;
    EstadoModelo estado_modelo;

    bool establecido = false;
    bool mostrando_grid = false;

    Estado(FaseNivel fase, const DatosNivel &);
};
