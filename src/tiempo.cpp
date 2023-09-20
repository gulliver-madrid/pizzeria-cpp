#include "tiempo.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <chrono>
#include <optional>

Tiempo Timer::obtener_tiempo_transcurrido() {
    assert(clock.has_value());
    float segundos = clock.value().getElapsedTime().asSeconds();
    return Tiempo::desde_segundos(segundos);
}

void Timer::start(Tiempo finalizacion) { //
    assert(finalizacion > Tiempo::CERO);
    this->finalizacion = finalizacion;
    clock.emplace();
}

bool Timer::termino() {
    assert(finalizacion != Tiempo::CERO);
    return obtener_tiempo_transcurrido() > finalizacion;
}

int TiempoPreparacion::obtener_porcentaje() const {
    int restante = finalizacion.obtener_milisegundos() -
                   obtener_tiempo_actual().obtener_milisegundos();
    if (restante < 0)
        restante = 0;
    int porcentaje = 100 - (restante * 100 / total.obtener_milisegundos());
    assert(porcentaje >= 0);
    return porcentaje;
};

/* Devuelve un objeto tiempo que cuenta el tiempo de manera circular por
 * periodos de 1000 segundos*/
Tiempo obtener_tiempo_actual() {
    auto ahora = std::chrono::system_clock::now();
    auto duracion = ahora.time_since_epoch();
    auto milisegundos =
        std::chrono::duration_cast<std::chrono::milliseconds>(duracion).count(
        ) %
        1'000'000;
    return Tiempo::desde_milisegundos(milisegundos);
};

Tiempo::Tiempo(int ms) : _ms(ms) {}
Tiempo Tiempo::desde_milisegundos(int valor) { return Tiempo{valor}; }
Tiempo Tiempo::desde_segundos(float valor) {
    return Tiempo{static_cast<int>(valor * 1000)};
}

const Tiempo Tiempo::CERO = Tiempo::desde_milisegundos(0);
