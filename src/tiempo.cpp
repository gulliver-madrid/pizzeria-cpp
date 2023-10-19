#include "tiempo.h"
#include "juego_assert.h"
#include <cassert>
#include <chrono>

bool Tiempo::operator<(const Tiempo &otro) const { // fmt
    return _ms < otro._ms;
}

int Tiempo::obtener_milisegundos() const { return _ms; }
const Tiempo Tiempo::operator+(const Tiempo &otro) const {
    return Tiempo{this->_ms + otro._ms};
}
const Tiempo Tiempo::operator-(const Tiempo &otro) const {
    return Tiempo{this->_ms - otro._ms};
}
bool Tiempo::operator==(const Tiempo &otro) const { return _ms == otro._ms; }

Tiempo Timer::obtener_tiempo_transcurrido() {
    assert(clock.has_value());
    auto segundos = clock.value().getElapsedTime().asSeconds();
    return Tiempo::desde_segundos(segundos);
}

void Timer::start(Tiempo finalizacion) {
    assert(finalizacion > Tiempo::CERO);
    assert(!this->finalizacion.has_value());
    this->finalizacion.emplace(finalizacion);
    clock.emplace();
}

bool Timer::termino() {
    juego_assert(this->finalizacion.has_value(), "Timer no inicializado");
    return obtener_tiempo_transcurrido() > finalizacion;
}

int TiempoPreparacion::obtener_porcentaje(const TiempoJuego &tiempo_actual
) const {
    const auto inicio = finalizacion - total;
    const auto transcurrido = tiempo_actual - inicio;
    int porcentaje = TiempoJuego::calcular_porcentaje(transcurrido, total);
    if (porcentaje > 100) {
        porcentaje = 100;
    }
    assert(porcentaje >= 0);
    return porcentaje;
};

/* Devuelve un objeto tiempo que cuenta el tiempo de manera circular por
 * periodos de 10_000 segundos
 */
Tiempo obtener_tiempo_actual() {
    auto ahora = std::chrono::system_clock::now();
    auto duracion = ahora.time_since_epoch();
    auto milisegundos =
        std::chrono::duration_cast<std::chrono::milliseconds>(duracion).count(
        ) %
        10'000'000;
    return Tiempo::desde_milisegundos(milisegundos);
};

Tiempo::Tiempo(int ms) : _ms(ms) {}
Tiempo Tiempo::desde_milisegundos(int valor) { return Tiempo{valor}; }
Tiempo Tiempo::desde_segundos(double valor) {
    return Tiempo{static_cast<int>(valor * 1000)};
}
TiempoJuego TiempoJuego::desde_milisegundos(int valor) {
    return TiempoJuego{valor};
}
TiempoJuego TiempoJuego::desde_segundos(double valor) {
    return TiempoJuego{static_cast<int>(valor * 1000)};
}
int TiempoJuego::calcular_porcentaje(
    const TiempoJuego &parte, const TiempoJuego &total
) {
    return parte._ms * 100 / total._ms;
}

const TiempoJuego TiempoJuego::operator+(const TiempoJuego &otro) const {
    return TiempoJuego{this->_ms + otro._ms};
}
const TiempoJuego TiempoJuego::operator-(const TiempoJuego &otro) const {
    return TiempoJuego{this->_ms - otro._ms};
}

TiempoJuego GestorTiempoJuego::obtener_tiempo_juego() {
    // TODO: implementar con pausas
    return TiempoJuego::desde_milisegundos(
        obtener_tiempo_actual().obtener_milisegundos()
    );
}

const Tiempo Tiempo::CERO = Tiempo::desde_milisegundos(0);
