#include "../modelo/modelo.h"
#include <gtest/gtest.h>

TEST(EvaluarPreparacionTest, NoHayPizzasEncargadas) {
    // No hay pizzas encargadas
    PizzasAContadores contadores;
    Encargos encargos;
    Tiempo tiempo_actual = Tiempo::desde_segundos(5);

    evaluar_preparacion(encargos, contadores, 3, tiempo_actual);

    EXPECT_TRUE(encargos.datos.empty());
    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 0);
}

TEST(EvaluarPreparacionTest, VariasPizzasPreparadas) {
    // 2 de los 3 encargos estan listos
    PizzasAContadores contadores;
    Encargos encargos;
    encargos.anadir(crear_encargo(TipoPizza::Margarita, Tiempo::CERO));
    encargos.anadir(crear_encargo(TipoPizza::Pepperoni, Tiempo::CERO));
    encargos.anadir(
        crear_encargo(TipoPizza::Pepperoni, Tiempo::desde_segundos(2))
    );
    Tiempo tiempo_actual = Tiempo::desde_segundos(5);

    evaluar_preparacion(encargos, contadores, 3, tiempo_actual);

    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(contadores[TipoPizza::Pepperoni].preparadas, 1);
    EXPECT_EQ(encargos.datos.size(), 1);
}

TEST(EvaluarPreparacionTest, LimiteMaximoDePizzas) {
    // Se preparan 3 pizzas pero el maximo que pueden salir de cocina es 2
    PizzasAContadores contadores;
    Encargos encargos;
    encargos.anadir(
        {TipoPizza::Margarita,
         {Tiempo::desde_segundos(4.5f), Tiempo::desde_segundos(2.5f)}}
    );
    encargos.anadir(
        {TipoPizza::Pepperoni,
         {Tiempo::desde_segundos(7.0f), Tiempo::desde_segundos(4.0f)}}
    );
    encargos.anadir(
        {TipoPizza::CuatroQuesos,
         {Tiempo::desde_segundos(8.0f), Tiempo::desde_segundos(7.0f)}}
    );

    Tiempo tiempo_actual = Tiempo::desde_segundos(10);

    evaluar_preparacion(encargos, contadores, 2, tiempo_actual);

    EXPECT_EQ(contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(contadores[TipoPizza::Pepperoni].preparadas, 1);

    EXPECT_EQ(encargos.datos.size(), 1);
    EXPECT_EQ(encargos.datos[0].tipo, TipoPizza::CuatroQuesos);
}
