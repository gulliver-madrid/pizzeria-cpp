#include "estado_nivel.h"
#include "general.h"
#include "modelo/datos_nivel.h"
#include <cassert>

//////// EstadoModelo

EstadoModelo::EstadoModelo(const DatosNivel &datos_nivel)
    : control_pizzas(datos_nivel.pedidos, datos_nivel.es_estatico) {
    assert(encargos.total() == 0);
    gestor_tiempo.reiniciar();
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
EstadoPreparacionPizzas
EstadoModelo::obtener_estado_preparacion_pizzas() const {
    const auto tiempo_actual = gestor_tiempo.obtener_tiempo_juego();
    return {encargos, tiempo_actual};
}

//////// Estado

Estado::Estado(FaseNivel fase, const DatosNivel &datos_nivel)
    : fase_actual(fase), estado_modelo(datos_nivel) {
    establecido = true;
}
