#include "../juego.h"
#include <gtest/gtest.h>

TEST(EvaluarPreparacionTest, NoHayPizzasPreparadas) {
    Estado estado;
    Tiempo tiempo_actual = Tiempo::desde_segundos(5);

    evaluar_preparacion(estado, 3, tiempo_actual);

    EXPECT_EQ(estado.encargadas.size(), 0);
    EXPECT_EQ(estado.contadores[Margarita].preparadas, 0);
}

TEST(EvaluarPreparacionTest, VariasPizzasPreparadas) {
    Estado estado;
    estado.encargadas.push_back(
        {TipoPizza::Margarita,
         {Tiempo::desde_segundos(2.5f), Tiempo::desde_segundos(2.5f)}}
    );
    estado.encargadas.push_back(
        {TipoPizza::Pepperoni,
         {Tiempo::desde_segundos(4.0f), Tiempo::desde_segundos(4.0f)}}
    );
    estado.encargadas.push_back(
        {TipoPizza::Pepperoni,
         {Tiempo::desde_segundos(6.0f), Tiempo::desde_segundos(4.0f)}}
    );

    Tiempo tiempo_actual = Tiempo::desde_segundos(5);

    evaluar_preparacion(estado, 3, tiempo_actual);

    EXPECT_EQ(estado.contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(estado.contadores[TipoPizza::Pepperoni].preparadas, 1);
    EXPECT_EQ(estado.encargadas.size(), 1);
}

TEST(EvaluarPreparacionTest, LimiteMaximoDePizzas) {
    Estado estado;
    estado.encargadas.push_back(
        {TipoPizza::Margarita,
         {Tiempo::desde_segundos(4.5f), Tiempo::desde_segundos(2.5f)}}
    );
    estado.encargadas.push_back(
        {TipoPizza::Pepperoni,
         {Tiempo::desde_segundos(7.0f), Tiempo::desde_segundos(4.0f)}}
    );
    estado.encargadas.push_back(
        {TipoPizza::CuatroQuesos,
         {Tiempo::desde_segundos(8.0f), Tiempo::desde_segundos(7.0f)}}
    );

    Tiempo tiempo_actual = Tiempo::desde_segundos(10);

    evaluar_preparacion(estado, 2, tiempo_actual);

    EXPECT_EQ(estado.contadores[TipoPizza::Margarita].preparadas, 1);
    EXPECT_EQ(estado.contadores[TipoPizza::Pepperoni].preparadas, 1);

    EXPECT_EQ(estado.encargadas.size(), 1);
    EXPECT_EQ(estado.encargadas[0].tipo, TipoPizza::CuatroQuesos);
}
