#include "tiempo.h"
#include "juego_assert.h"
#include "templates/helpers.h"
#include <cassert>
#include <chrono>

namespace {
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

    int calcular_porcentaje(const sf::Time &parte, const sf::Time &total) {
        return static_cast<int>((parte / total) * 100);
    }
} // namespace

namespace tiempo {
    std::string time_to_string(sf::Time time) {
        int ms = time.asMilliseconds();
        const int segundos_brutos = ms / 1000;
        const auto minutos = segundos_brutos / 60;
        const auto segundos = segundos_brutos % 60;
        assert(segundos < 60);
        return pad_with_zeroes(minutos) + ":" + pad_with_zeroes(segundos);
    }

    /* Devuelve un objeto tiempo que cuenta el tiempo de manera circular por
     * periodos de 10_000 segundos
     */
    sf::Time obtener_tiempo_actual() {
        auto ahora = std::chrono::system_clock::now();
        auto duracion = ahora.time_since_epoch();
        auto ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(duracion) //
                .count() %
            10'000'000;
        const static auto inicial = sf::milliseconds((int)ms);
        return sf::milliseconds((int)ms) - inicial;
    };
} // namespace tiempo

///////////////////////////////////////////
// TiempoPreparacion
//////////////////////////////////////////

int TiempoPreparacion::obtener_porcentaje(const sf::Time &tiempo_actual) const {
    const auto inicio = finalizacion - total;
    const auto transcurrido = tiempo_actual - inicio;
    int porcentaje = calcular_porcentaje(transcurrido, total);
    if (porcentaje > 100) {
        porcentaje = 100;
    }
    assert(porcentaje >= 0);
    return porcentaje;
};

///////////////////////////////////////////
// GestorTiempoJuego
//////////////////////////////////////////

sf::Time GestorTiempoControlable::obtener_tiempo_transcurrido() const {
    return _actual;
}

void GestorTiempoControlable::tick(sf::Time transcurrido) {
    if (en_pausa)
        return;
    _actual = _actual + transcurrido;
}
void GestorTiempoControlable::activar() {
    assert(en_pausa);
    en_pausa = false;
}

void GestorTiempoControlable::pausar() {
    assert(!en_pausa);
    en_pausa = true;
}
void GestorTiempoControlable::reiniciar() {
    en_pausa = true;
    _actual = sf::Time::Zero;
}

///////////////////////////////////////////
// GestorTimer
//////////////////////////////////////////

sf::Time GestorTimer::obtener_tiempo_transcurrido() const {
    return _gestor_interno.obtener_tiempo_transcurrido();
}

void GestorTimer::start(sf::Time finalizacion_) {
    assert(finalizacion_ > sf::Time::Zero);
    assert(!this->finalizacion.has_value());
    this->finalizacion.emplace(finalizacion_);
    _gestor_interno.activar(); //
}

void GestorTimer::tick(sf::Time transcurrido) {
    _gestor_interno.tick(transcurrido);
}

bool GestorTimer::termino() {
    juego_assert(this->finalizacion.has_value(), "Timer no inicializado");
    return obtener_tiempo_transcurrido() > finalizacion;
}

///////////////////////////////////////////
// GestorTiempoGeneral
//////////////////////////////////////////
void GestorTiempoGeneral::anade_gestor(
    TipoGestorTiempo clave, std::shared_ptr<GestorTiempo> gestor
) {
    assert(!has_key(gestores, clave));
    gestores[clave] = gestor;
}

void GestorTiempoGeneral::tick(sf::Time tiempo) {
    for (auto &[_, gestor] : gestores) {
        gestor->tick(tiempo);
    }
}

std::shared_ptr<GestorTimer>
GestorTiempoGeneral::get_timer(TipoGestorTiempo clave) {
    auto g = gestores.at(clave);
    auto gestor = std::dynamic_pointer_cast<GestorTimer>(g);
    assert(gestor);
    return gestor;
}
std::shared_ptr<GestorTimer>
GestorTiempoGeneral::get_const_timer(TipoGestorTiempo clave) const {
    auto g = gestores.at(clave);
    auto gestor = std::dynamic_pointer_cast<GestorTimer>(g);
    assert(gestor);
    return gestor;
}

std::shared_ptr<GestorTiempoControlable>
GestorTiempoGeneral::get_gestor_tiempo_controlable( //
    TipoGestorTiempo clave
) {
    auto g = gestores.at(clave);
    auto gestor = std::dynamic_pointer_cast<GestorTiempoControlable>(g);
    assert(gestor);
    return gestor;
}
