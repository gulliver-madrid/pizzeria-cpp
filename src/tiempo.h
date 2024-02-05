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
    std::string time_to_string(sf::Time time);
} // namespace tiempo

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
    virtual sf::Time obtener_tiempo_transcurrido() const = 0;
};

///////////////////////////////////////////
// GestorTiempoControlable
//////////////////////////////////////////

struct GestorTiempoControlable : public GestorTiempo {
    // Debe activarse para poder utilizarlo

  private:
    sf::Time _actual = sf::Time::Zero;
    bool en_pausa = true;

  public:
    virtual void tick(sf::Time tiempo) override;
    virtual sf::Time obtener_tiempo_transcurrido() const override;
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
    GestorTiempoControlable _gestor_interno;
    std::optional<sf::Time> finalizacion = std::nullopt;
    virtual sf::Time obtener_tiempo_transcurrido() const override;

  public:
    void start(sf::Time finalizacion);
    virtual void tick(sf::Time tiempo) override;
    bool termino();
};

enum class TipoGestorTiempo {
    timer_antes_resultado,
    timer_fin_nivel,
    gestor_tiempo_juego,
    gestor_tiempo_real
};

struct GestorTiempoGeneral {
    std::map<TipoGestorTiempo, std::shared_ptr<GestorTiempo>> gestores;
    void anade_gestor(TipoGestorTiempo, std::shared_ptr<GestorTiempo>);
    void tick(sf::Time tiempo);
    std::shared_ptr<GestorTimer> get_timer(TipoGestorTiempo);
    std::shared_ptr<GestorTimer> get_const_timer(TipoGestorTiempo) const;
    std::shared_ptr<GestorTiempoControlable>
        get_gestor_tiempo_controlable(TipoGestorTiempo);
};
