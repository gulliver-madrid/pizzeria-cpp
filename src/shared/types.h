#pragma once

#include <cassert>
#include <iostream>
#include <string>

class UInt {
  private:
    int value;

  public:
    UInt(int v) : value(v) { assert(value >= 0); }
    UInt operator+(UInt other) const { return UInt(value + other.value); }
    UInt operator-(UInt other) const {
        const int resta = value - other.value;
        assert(resta >= 0);
        return UInt(resta);
    }

    // Operador +=
    UInt &operator+=(UInt other) {
        value += other.value;
        return *this;
    }

    // Incremento prefijo
    UInt &operator++() {
        ++value;
        return *this;
    }

    // Incremento sufijo
    UInt operator++(int) {
        UInt temp(*this);
        ++value;
        return temp;
    }

    // Decremento prefijo
    UInt &operator--() {
        assert(value > 0); // Asegurarse de que el valor nunca sea negativo
        --value;
        return *this;
    }

    // Decremento sufijo
    UInt operator--(int) {
        assert(value > 0); // Asegurarse de que el valor nunca sea negativo
        UInt temp(*this);
        --value;
        return temp;
    }

    // Mayor que (>)
    bool operator>(UInt other) const { return value > other.value; }

    // Menor que (<)
    bool operator<(UInt other) const { return value < other.value; }

    // Menor o igual que (<=)
    bool operator<=(UInt other) const { return value <= other.value; }

    // Mayor o igual que (>=)
    bool operator>=(UInt other) const { return value >= other.value; }

    // Distinto (!=)
    bool operator!=(UInt other) const { return value != other.value; }

    // Igual (==)
    bool operator==(UInt other) const { return value == other.value; }

    // Conversion a int
    int to_int() const { return value; }

    // Conversion a string
    std::string to_string() const { return std::to_string(value); }

    // Sobrecarga del operador << para iostream
    friend std::ostream &operator<<(std::ostream &os, const UInt &u) {
        os << u.value;
        return os;
    }
};
