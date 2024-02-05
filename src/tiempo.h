#pragma once

#include "templates/comparable.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <map>
#include <memory>
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
    sf::Time obtener_tiempo_transcurrido();

  public:
    void start(sf::Time finalizacion);
    bool termino();
};

///////////////////////////////////////////
// TiempoPreparacion
//////////////////////////////////////////

struct TiempoPreparacion {
    // Tiempo en el que la pizza estara lista
    const sf::Time finalizacion;
    // Tiempo total de preparacion en milisegundos
    const sf::Time total;
    int obtener_porcentaje(const sf::Time &tiempo_actual) const;
};

// Clase base para gestores de tiempo que usan tick()
struct GestorTiempo {
    virtual void tick(sf::Time tiempo) = 0;
};

///////////////////////////////////////////
// GestorTiempoJuego
//////////////////////////////////////////

struct GestorTiempoJuego : public GestorTiempo {
    // Debe activarse para poder utilizarlo

  private:
    sf::Time _actual = sf::Time::Zero;
    bool en_pausa = true;

  public:
    sf::Time obtener_tiempo_juego() const;
    virtual void tick(sf::Time tiempo) override;
    void activar();
    void pausar();
    void reiniciar();
};

///////////////////////////////////////////
// GestorTimer
//////////////////////////////////////////

// La idea de esta clase es que sea el sustituto de Timer que usa tick(), de
// manera que no incluya un Clock interno.

struct GestorTimer : public GestorTiempo {
  private:
    GestorTiempoJuego _gestor_interno;
    std::optional<sf::Time> finalizacion = std::nullopt;
    sf::Time obtener_tiempo_transcurrido();

  public:
    void start(sf::Time finalizacion);
    virtual void tick(sf::Time tiempo) override;
    bool termino();
};

enum class GestorTiempoKey {
    timer_espera_antes_de_resultado,
    timer_fin_nivel,
    gestor_tiempo_juego,
};

struct GestorTiempoGeneral : public GestorTiempo {
    std::map<GestorTiempoKey, std::shared_ptr<GestorTiempo>> gestores;
    void tick(sf::Time tiempo) {
        for (auto &[_, gestor] : gestores) {
            gestor->tick(tiempo);
        }
    }
};
