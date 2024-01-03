#pragma once

#include "templates/comparable.h"
#include <SFML/System/Clock.hpp>
#include <optional>
#include <string>

///////////////////////////////////////////
// Tiempo
//////////////////////////////////////////

struct Tiempo : public templates::Comparable<Tiempo> {
  protected:
    // Guarda el valor en milisegundos del objeto Tiempo
    int _ms;
    Tiempo(int ms);

  public:
    static const Tiempo CERO;
    static Tiempo desde_milisegundos(int valor);
    static Tiempo desde_segundos(double valor);

    int obtener_milisegundos() const;
    const Tiempo operator+(const Tiempo &otro) const;
    const Tiempo operator-(const Tiempo &otro) const;
    bool operator==(const Tiempo &otro) const;
    bool operator<(const Tiempo &otro) const;
    virtual std::string to_string() const;
};
namespace tiempo {
    Tiempo obtener_tiempo_actual();
}

///////////////////////////////////////////
// TiempoJuego
//////////////////////////////////////////

struct TiempoJuego : public Tiempo {
  private:
    TiempoJuego(int ms) : Tiempo(ms) {}

  public:
    TiempoJuego(const TiempoJuego &src) : Tiempo(src.obtener_milisegundos()) {}

    static TiempoJuego desde_milisegundos(int valor);
    static TiempoJuego desde_segundos(double valor);
    static int calcular_porcentaje( //
        const TiempoJuego &parte, const TiempoJuego &total
    );
    const TiempoJuego operator+(const TiempoJuego &otro) const;
    const TiempoJuego operator-(const TiempoJuego &otro) const;
};

const auto TiempoJuego_CERO = TiempoJuego::desde_milisegundos(0);

///////////////////////////////////////////
// Timer
//////////////////////////////////////////

struct Timer {
  private:
    std::optional<sf::Clock> clock;
    std::optional<Tiempo> finalizacion = std::nullopt;
    Tiempo obtener_tiempo_transcurrido();

  public:
    void start(Tiempo finalizacion);
    bool termino();
};

///////////////////////////////////////////
// TiempoPreparacion
//////////////////////////////////////////

struct TiempoPreparacion {
    // Tiempo en el que la pizza estara lista
    TiempoJuego finalizacion;
    // Tiempo total de preparacion en milisegundos
    TiempoJuego total;
    int obtener_porcentaje(const TiempoJuego &tiempo_actual) const;
};

///////////////////////////////////////////
// GestorTiempoJuego
//////////////////////////////////////////

struct GestorTiempoJuego {
    // Debe activarse para poder utilizarlo

  private:
    TiempoJuego _actual = TiempoJuego_CERO;
    bool en_pausa = true;

  public:
    TiempoJuego obtener_tiempo_juego() const;
    void tick(TiempoJuego tiempo);
    void activar();
    void pausar();
    void reiniciar();
};
