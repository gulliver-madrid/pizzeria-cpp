#include "modelo_amplio.h"
#include "../observador_fase.h"
#include "comandos.h"

ModeloAmplio::ModeloAmplio(
    const std::optional<DatosModeloInterno> datos_modelo_interno
)
    : modelo_interno(datos_modelo_interno) {
    establecido = true;
}

void ModeloAmplio::set_fase_actual(FaseNivel nueva) { //
    if (nueva == fase_actual)
        return;
    fase_actual = nueva;
    for (auto observador : observadores_fase) {
        observador->on_cambio_de_fase(nueva);
    }
}

FaseNivel ModeloAmplio::get_fase_actual() const { //
    return fase_actual;
}

sf::Time ModeloAmplio::obtener_tiempo_transcurrido() const {
    return gestor_tiempo_general.gestores
        .at(TipoGestorTiempo::gestor_tiempo_real)
        ->obtener_tiempo_transcurrido();
}

void ModeloAmplio::activar_tiempo_juego() {
    auto gestor_tiempo_juego =
        gestor_tiempo_general.get_gestor_tiempo_controlable(
            TipoGestorTiempo::gestor_tiempo_juego
        );
    gestor_tiempo_juego->activar();
}
void ModeloAmplio::iniciar_espera_antes_resultado() {
    gestor_tiempo_general
        .get_gestor_tiempo_controlable(TipoGestorTiempo::gestor_tiempo_juego)
        ->pausar();
    gestor_tiempo_general.get_timer(TipoGestorTiempo::timer_antes_resultado)
        ->start(tiempos::RETARDO_ANTES_DE_RESULTADO);
}
void ModeloAmplio::iniciar_espera_entre_niveles() {
    auto timer_fin_nivel =
        gestor_tiempo_general.get_timer(TipoGestorTiempo::timer_fin_nivel);
    timer_fin_nivel->start(tiempos::ESPERA_ENTRE_NIVELES);
}

bool ModeloAmplio::termino_timer(TipoGestorTiempo clave) const {
    auto timer = gestor_tiempo_general.get_const_timer(clave);
    return timer->termino();
}
