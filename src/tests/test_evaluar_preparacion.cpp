#include "../modelo/modelo.h"
#include <gtest/gtest.h>

TEST(EvaluarPreparacionTest, NoHayPizzasEncargadas) {
    // No hay pizzas encargadas
    PizzasAContadores contadores;
    std::vector<EncargoACocina> encargos;
    Tiempo tiempo_actual = Tiempo::desde_segundos(5);

    evaluar_preparacion(encargos, contadores, 3, tiempo_actual);

    EXPECT_EQ(encargos.size(), 0);
    EXPECT_EQ(contadores[Margarita].preparadas, 0);
}

TEST(EvaluarPreparacionTest, VariasPizzasPreparadas) {
    // 2 de los 3 encargos estan listos
    PizzasAContadores contadores;
    std::vector<EncargoACocina> encargos;
    encargos.push_back(crear_encargo(TipoPizza::Margarita, Tiempo::CERO));
    encargos.push_back(crear_encargo(TipoPizza::Pepperoni, Tiempo::CERO));
    encargos.push_back(
        crear_encargo(TipoPizza::Pepperoni, Tiempo::desde_segundos(2))
    );
    Tiempo tiempo_actual = Tiempo::desde_segundos(5);

    evaluar_preparacion(encargos, contadores, 3, tiempo_actual);

    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(contadores[TipoPizza::Pepperoni].preparadas, 1);
    EXPECT_EQ(encargos.size(), 1);
}

TEST(EvaluarPreparacionTest, LimiteMaximoDePizzas) {
    // Se preparan 3 pizzas pero el maximo que pueden salir de cocina es 2
    PizzasAContadores contadores;
    std::vector<EncargoACocina> encargos;
    encargos.push_back(
        {TipoPizza::Margarita,
         {Tiempo::desde_segundos(4.5f), Tiempo::desde_segundos(2.5f)}}
    );
    encargos.push_back(
        {TipoPizza::Pepperoni,
         {Tiempo::desde_segundos(7.0f), Tiempo::desde_segundos(4.0f)}}
    );
    encargos.push_back(
        {TipoPizza::CuatroQuesos,
         {Tiempo::desde_segundos(8.0f), Tiempo::desde_segundos(7.0f)}}
    );

    Tiempo tiempo_actual = Tiempo::desde_segundos(10);

    evaluar_preparacion(encargos, contadores, 2, tiempo_actual);

    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(contadores[TipoPizza::Pepperoni].preparadas, 1);

    EXPECT_EQ(encargos.size(), 1);
    EXPECT_EQ(encargos[0].tipo, TipoPizza::CuatroQuesos);
}
