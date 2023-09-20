#include "tiempo.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <chrono>
#include <optional>

float Timer::get_seconds() {
    assert(clock.has_value());
    float seconds = clock.value().getElapsedTime().asSeconds();
    return seconds;
}

void Timer::start(float finalizacion) { //
    assert(finalizacion > 0);
    this->finalizacion = finalizacion;
    clock.emplace();
}

bool Timer::termino() {
    assert(finalizacion);
    return get_seconds() > finalizacion;
}

int TiempoPreparacion::obtener_porcentaje() const {
    int restante = lista - obtener_milisegundos_actuales();
    if (restante < 0)
        restante = 0;
    int porcentaje = 100 - (restante * 100 / total);
    assert(porcentaje >= 0);
    return porcentaje;
};

int obtener_milisegundos_actuales() {
    auto ahora = std::chrono::system_clock::now();
    auto duracion = ahora.time_since_epoch();
    auto milisegundos =
        std::chrono::duration_cast<std::chrono::milliseconds>(duracion).count(
        ) %
        1'000'000;
    return milisegundos;
};
