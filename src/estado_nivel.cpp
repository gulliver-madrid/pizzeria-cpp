#include "estado_nivel.h"
#include "general.h"

//////// EstadoModelo

EstadoModelo::EstadoModelo(modelo::ControlPizzas &control)
    : control_pizzas(control) {
    assert(encargos.total() == 0);
}

/* Encarga una pizza de tipo tp */
void EstadoModelo::anadir_encargo(dominio::TipoPizza tp) {
    auto encargo = EncargoACocina( //
        tp, gestor_tiempo.obtener_tiempo_juego()
    );
    encargos.anadir(encargo);
}

//////// Estado

Estado::Estado(FaseNivel fase, modelo::ControlPizzas &control)
    : fase_actual(fase), estado_modelo(control) {
    fase_actual = FaseNivel::MostrandoInstrucciones;
    establecido = true;
}
