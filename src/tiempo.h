#pragma once

#include "templates.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <optional>

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
};

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

struct Timer {
  private:
    std::optional<sf::Clock> clock;
    std::optional<Tiempo> finalizacion = std::nullopt;
    Tiempo obtener_tiempo_transcurrido();

  public:
    void start(Tiempo finalizacion);
    bool termino();
};

struct TiempoPreparacion {
    // Tiempo en el que la pizza estará lista
    TiempoJuego finalizacion;
    // Tiempo total de preparación en milisegundos
    TiempoJuego total;
    int obtener_porcentaje(const TiempoJuego &tiempo_actual) const;
};

Tiempo obtener_tiempo_actual();

/* Provisional. Debe poder activarse y pausarse */
struct GestorTiempoJuego {

  private:
    TiempoJuego contabilizado = TiempoJuego_CERO;
    Tiempo ultima_contabilizacion = Tiempo::CERO;
    bool en_pausa = true;
    void contabilizar() {
        const auto actual = obtener_tiempo_actual();
        const auto transcurrido = actual - ultima_contabilizacion;
        contabilizado = TiempoJuego::desde_milisegundos(
            contabilizado.obtener_milisegundos() +
            transcurrido.obtener_milisegundos()
        );
    }

  public:
    GestorTiempoJuego() {}
    static TiempoJuego obtener_tiempo_juego();
    void activar() {
        assert(en_pausa);
        en_pausa = false;
    }
    void pausar() {
        assert(!en_pausa);
        en_pausa = true;
    }
    TiempoJuego obtener_transcurrido() { return contabilizado; }
};
