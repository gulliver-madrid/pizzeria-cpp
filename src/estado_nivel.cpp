#include "estado_nivel.h"
#include "general.h"
#include "modelo/control_pizzas.h"

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

/*
 * Despacha una pizza a los clientes del tipo indicado. Devuelve true si ya
 * se han cubierto todos los pedidos, y false en caso contrario.
 */
bool EstadoModelo::despachar_pizza( //
    const dominio::TipoPizza tp
) {
    control_pizzas.procesar_despacho(tp);
    return (!control_pizzas.faltan_pedidos_por_cubrir());
}

//////// Estado

Estado::Estado(FaseNivel fase, modelo::ControlPizzas &control)
    : fase_actual(fase), estado_modelo(control) {
    fase_actual = FaseNivel::MostrandoInstrucciones;
    establecido = true;
}
