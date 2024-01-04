#include "encargos.h"
#include "dominio.h"

using dominio::TipoPizza;

// En segundos
const std::map<TipoPizza, sf::Time> tiempos_preparacion = {
    {TipoPizza::Margarita, sf::seconds(2.5)},
    {TipoPizza::Pepperoni, sf::seconds(4.0)},
    {TipoPizza::CuatroQuesos, sf::seconds(7.0)},
};

/*
 * Calcula el tiempo de preparacion para una pizza partiendo de su tipo y del
 * tiempo actual.
 */
TiempoPreparacion calcular_tiempo_preparacion( //
    const TipoPizza tipo, const sf::Time &tiempo_actual
) {
    auto total = tiempos_preparacion.at(tipo);
    return TiempoPreparacion{tiempo_actual + total, total};
}

EncargoACocina::EncargoACocina(
    const TipoPizza tipo, const sf::Time &tiempo_actual
)
    : tipo(tipo),
      tiempo_preparacion(calcular_tiempo_preparacion(tipo, tiempo_actual)) {}

// Definicion metodos Encargos

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

// Fin metodos Encargos
