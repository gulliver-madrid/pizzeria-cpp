#include "tiempo.h"
#include "juego_assert.h"
#include <cassert>
#include <chrono>

// Asignacion miembros estaticos
TiempoJuego GestorTiempoJuego::previo = TiempoJuego_CERO;
Tiempo GestorTiempoJuego::ultima_activacion = Tiempo::CERO;
bool GestorTiempoJuego::en_pausa = true;

std::string pad_with_zeroes(int n) {
    assert(n >= 0);
    if (n > 59) {
        n = n % 60;
    }
    auto cadena = std::to_string(n);
    if (cadena.length() == 1) {
        cadena.insert(0, "0");
    }
    return cadena;
}

///////////////////////////////////////////
// Tiempo
//////////////////////////////////////////

bool Tiempo::operator<(const Tiempo &otro) const { //
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

Tiempo::Tiempo(int ms) : _ms(ms) {}
Tiempo Tiempo::desde_milisegundos(int valor) { return Tiempo{valor}; }
Tiempo Tiempo::desde_segundos(double valor) {
    return Tiempo{static_cast<int>(valor * 1000)};
}

std::string Tiempo::to_string() const {
    const int segundos_brutos = _ms / 1000;
    const auto minutos = segundos_brutos / 60;
    const auto segundos = segundos_brutos % 60;
    assert(segundos < 60);
    return pad_with_zeroes(minutos) + ":" + pad_with_zeroes(segundos);
}

///////////////////////////////////////////
// Timer
//////////////////////////////////////////

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

///////////////////////////////////////////
// TiempoPreparacion
//////////////////////////////////////////

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
    const static auto inicial = Tiempo::desde_milisegundos(milisegundos);
    return Tiempo::desde_milisegundos(milisegundos) - inicial;
};

///////////////////////////////////////////
// TiempoJuego
//////////////////////////////////////////

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

///////////////////////////////////////////
// GestorTiempoJuego
//////////////////////////////////////////

TiempoJuego GestorTiempoJuego::obtener_tiempo_juego() {
    if (en_pausa) {
        return previo;
    }
    const auto transcurrido = obtener_tiempo_actual() - ultima_activacion;
    return previo +
           TiempoJuego::desde_milisegundos(transcurrido.obtener_milisegundos());
}

void GestorTiempoJuego::activar() {
    assert(en_pausa);
    ultima_activacion = obtener_tiempo_actual();
    en_pausa = false;
}
void GestorTiempoJuego::pausar() {
    assert(!en_pausa);
    previo = obtener_tiempo_juego();
    en_pausa = true;
}
void GestorTiempoJuego::reiniciar() {
    en_pausa = true;
    previo = TiempoJuego_CERO;
    ultima_activacion = Tiempo::CERO;
}

const Tiempo Tiempo::CERO = Tiempo::desde_milisegundos(0);
