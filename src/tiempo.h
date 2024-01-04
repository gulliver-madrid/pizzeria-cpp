#pragma once

#include "templates/comparable.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <optional>
#include <string>

namespace tiempo {
    sf::Time obtener_tiempo_actual();
}

std::string time_to_string(sf::Time time);

///////////////////////////////////////////
// Timer
//////////////////////////////////////////

struct Timer {
  private:
    std::optional<sf::Clock> clock;
    std::optional<sf::Time> finalizacion = std::nullopt;
    sf::Time Timer::obtener_tiempo_transcurrido();

  public:
    void Timer::start(sf::Time finalizacion);
    bool termino();
};

///////////////////////////////////////////
// TiempoPreparacion
//////////////////////////////////////////

struct TiempoPreparacion {
    // Tiempo en el que la pizza estara lista
    sf::Time finalizacion;
    // Tiempo total de preparacion en milisegundos
    sf::Time total;
    int obtener_porcentaje(const sf::Time &tiempo_actual) const;
};

///////////////////////////////////////////
// GestorTiempoJuego
//////////////////////////////////////////

struct GestorTiempoJuego {
    // Debe activarse para poder utilizarlo

  private:
    sf::Time _actual = sf::Time::Zero;
    bool en_pausa = true;

  public:
    sf::Time obtener_tiempo_juego() const;
    void tick(sf::Time tiempo);
    void activar();
    void pausar();
    void reiniciar();
};
