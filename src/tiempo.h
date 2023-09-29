#pragma once

#include "templates.h"
#include <SFML/Graphics.hpp>
#include <optional>

struct Tiempo : public Comparable<Tiempo> {
  private:
    // Guarda el valor en milisegundos del objeto Tiempo
    const int _ms;
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
    static int calcular_porcentaje(const Tiempo &parte, const Tiempo &total);
};

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
    // Tiempo unix en el que la pizza estará lista
    Tiempo finalizacion;
    // Tiempo total de preparación en milisegundos
    Tiempo total;
    int obtener_porcentaje() const;
};

Tiempo obtener_tiempo_actual();
