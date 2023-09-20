#pragma once

#include "comparable.h"
#include <SFML/Graphics.hpp>
#include <optional>

struct Tiempo : public Comparable<Tiempo> {
  private:
    // Guarda el valor en milisegundos del objeto Tiempo. Este campo no debe
    // modificarse
    int _ms;
    Tiempo(int ms);

  public:
    static const Tiempo CERO;
    static Tiempo desde_milisegundos(int valor);
    static Tiempo desde_segundos(float valor);
    // Solo para depuración o pruebas
    int obtener_milisegundos() const { return _ms; }
    const Tiempo operator+(const Tiempo &otro) const {
        return Tiempo{this->_ms + otro._ms};
    }
    const Tiempo operator-(const Tiempo &otro) const {
        return Tiempo{this->_ms - otro._ms};
    }
    bool operator==(const Tiempo &otro) const { return _ms == otro._ms; }
    bool operator<(const Tiempo &otro) const { return _ms < otro._ms; }
    static int calcular_porcentaje(const Tiempo &parte, const Tiempo &total);
};

struct Timer {
  private:
    std::optional<sf::Clock> clock;
    Tiempo finalizacion = Tiempo::CERO;
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
