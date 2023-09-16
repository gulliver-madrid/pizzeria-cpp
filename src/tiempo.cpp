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
