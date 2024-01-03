
#include "../tiempo.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Tiempo, RestarTiempo) { //
    const Tiempo t1 = Tiempo::desde_milisegundos(1);
    const Tiempo t2 = Tiempo::desde_milisegundos(3);
    EXPECT_EQ(t2 - t1, Tiempo::desde_milisegundos(2));
}
TEST(Tiempo, GestorTiempoJuegoTick) { //
    GestorTiempoJuego gestor_tiempo;
    gestor_tiempo.activar();
    gestor_tiempo.tick(TiempoJuego::desde_milisegundos(40));
    EXPECT_EQ(gestor_tiempo.obtener_tiempo_juego().obtener_milisegundos(), 40);
}
TEST(Tiempo, GestorTiempoJuegoTickSinActivar) { //
    GestorTiempoJuego gestor_tiempo;
    gestor_tiempo.tick(TiempoJuego::desde_milisegundos(40));
    EXPECT_EQ(gestor_tiempo.obtener_tiempo_juego().obtener_milisegundos(), 0);
}
