#include "../../modelo/encargos.h"
#include "../../modelo/modelo.h"
#include "../../tiempo.h"
#include <gtest/gtest.h>

using dominio::TipoPizza;
using modelo::PizzasAContadores;

TEST(EvaluarPreparacion, NoHayPizzasEncargadas) {
    // No hay pizzas encargadas
    PizzasAContadores contadores;
    Encargos encargos;
    const auto tiempo_actual = sf::seconds(5);

    evaluar_preparacion(encargos, contadores, 3, tiempo_actual);

    EXPECT_EQ(encargos.total(), 0);
    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 0);
}

TEST(EvaluarPreparacion, VariasPizzasPreparadas) {
    // 2 de los 3 encargos estan listos
    PizzasAContadores contadores;
    Encargos encargos;
    encargos.anadir(EncargoACocina(TipoPizza::Margarita, sf::Time::Zero));
    encargos.anadir(EncargoACocina(TipoPizza::Pepperoni, sf::Time::Zero));
    encargos.anadir(EncargoACocina(TipoPizza::Pepperoni, sf::seconds(2)));
    const auto tiempo_actual = sf::seconds(5);

    evaluar_preparacion(encargos, contadores, 3, tiempo_actual);

    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(contadores[TipoPizza::Pepperoni].preparadas, 1);
    EXPECT_EQ(encargos.total(), 1);
}

TEST(EvaluarPreparacion, LimiteMaximoDePizzas) {
    // Se preparan 3 pizzas pero el maximo que pueden salir de cocina es 2
    PizzasAContadores contadores;
    Encargos encargos;
    std::pair<TipoPizza, float> data[] = {
        {TipoPizza::Margarita, 2.5f},
        {TipoPizza::Pepperoni, 4.0f},
        {TipoPizza::CuatroQuesos, 7.0f},
    };
    for (const auto &encargo : data) {
        encargos.anadir(
            EncargoACocina(encargo.first, sf::seconds(encargo.second))
        );
    }
    const auto tiempo_actual = sf::seconds(10);

    const int maximo = 2;
    evaluar_preparacion(encargos, contadores, maximo, tiempo_actual);

    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(contadores[TipoPizza::Pepperoni].preparadas, 1);
    EXPECT_EQ(contadores[TipoPizza::CuatroQuesos].preparadas, 0);

    EXPECT_EQ(encargos.total(), 1);
    EXPECT_EQ(encargos.por_indice(0).tipo, TipoPizza::CuatroQuesos);
}
