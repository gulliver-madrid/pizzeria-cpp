#include "encargos.h"

// En segundos
std::map<TipoPizza, float> tiempos_preparacion = {
    {TipoPizza::Margarita, 2.5f},
    {TipoPizza::Pepperoni, 4.0f},
    {TipoPizza::CuatroQuesos, 7.0f},
};

EncargoACocina::EncargoACocina(
    const TipoPizza tipo, const TiempoPreparacion tiempo_preparacion
)
    : tipo(tipo), tiempo_preparacion(tiempo_preparacion) {}

EncargoACocina
EncargoACocina::crear(const TipoPizza &tipo, Tiempo tiempo_actual) {
    auto total = Tiempo::desde_segundos(tiempos_preparacion[tipo]);
    auto tiempo_preparacion = TiempoPreparacion{
        tiempo_actual + total, total // fmt
    };
    return EncargoACocina{tipo, tiempo_preparacion};
}

// Definición métodos Encargos

int Encargos::del_tipo(TipoPizza tipo) const {
    int contador = 0;
    for (auto &encargo : _datos) {
        if (encargo.tipo == tipo) {
            contador++;
        }
    }
    return contador;
}

void Encargos::anadir(const EncargoACocina encargo) {
    _datos.push_back(encargo);
}

std::vector<EncargoACocina>::const_iterator Encargos::begin() const {
    return _datos.cbegin();
}

std::vector<EncargoACocina>::const_iterator Encargos::end() const {
    return _datos.cend();
}

int Encargos::total() const { // fmt
    return _datos.size();
}

EncargoACocina Encargos::por_indice(int i) const { // fmt
    return _datos.at(i);
}

// Fin métodos Encargos
