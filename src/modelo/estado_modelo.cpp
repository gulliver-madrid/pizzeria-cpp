#include "estado_modelo.h"
#include "datos_nivel_para_modelo.h"

//////// EstadoModelo

EstadoModelo::EstadoModelo(const DatosNivelParaModelo &datos_nivel)
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

TiempoJuego EstadoModelo::obtener_tiempo_juego() const {
    return gestor_tiempo.obtener_tiempo_juego();
}

void EstadoModelo::evaluar_preparacion_pizzas() {
    int total_preparadas = control_pizzas.obtener_total_preparadas();
    int preparables = modelo_info::MAXIMO_PIZZAS_PREPARADAS - total_preparadas;
    if (preparables > 0) {
        const auto tiempo_actual = gestor_tiempo.obtener_tiempo_juego();
        evaluar_preparacion(
            encargos, control_pizzas.contadores, preparables, tiempo_actual
        );
    }
}

/*
 * Solo tiene sentido en modo estatico.
 */
bool EstadoModelo::objetivos_sobrepasados(dominio::TipoPizza tp) const {
    if (!control_pizzas.es_estatico.valor)
        return false;
    const auto &pedidos = control_pizzas.pedidos;
    assert(pedidos.size() == 1);
    const auto &pedido = pedidos[0];
    auto &contadores_tp = control_pizzas.contadores.at(tp);
    int potenciales = contadores_tp.preparadas + contadores_tp.servidas +
                      encargos.del_tipo(tp);
    auto contador_estatico_tp = pedido.contenido.at(tp);
    return (potenciales >= contador_estatico_tp.objetivo);
}
