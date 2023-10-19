#include "encargos.h"
#include "dominio.h"

using modelo::TipoPizza;

// En segundos
const std::map<TipoPizza, TiempoJuego> tiempos_preparacion = {
    {TipoPizza::Margarita, TiempoJuego::desde_segundos(2.5)},
    {TipoPizza::Pepperoni, TiempoJuego::desde_segundos(4.0)},
    {TipoPizza::CuatroQuesos, TiempoJuego::desde_segundos(7.0)},
};

/*
 * Calcula el tiempo de preparacion para una pizza partiendo de su tipo y del
 * tiempo actual.
 */
TiempoPreparacion calcular_tiempo_preparacion( //
    const TipoPizza tipo, const TiempoJuego &tiempo_actual
) {
    auto total = tiempos_preparacion.at(tipo);
    return TiempoPreparacion{tiempo_actual + total, total};
}

EncargoACocina::EncargoACocina(
    const TipoPizza tipo, const TiempoJuego &tiempo_actual
)
    : tipo(tipo),
      tiempo_preparacion(calcular_tiempo_preparacion(tipo, tiempo_actual)) {}

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
