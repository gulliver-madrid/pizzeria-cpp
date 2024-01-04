
#include "../tiempo.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Tiempo, RestarTiempo) { //
    const sf::Time t1 = sf::milliseconds(1);
    const sf::Time t2 = sf::milliseconds(3);
    EXPECT_EQ(t2 - t1, sf::milliseconds(2));
}
TEST(Tiempo, GestorTiempoJuegoTick) { //
    GestorTiempoJuego gestor_tiempo;
    gestor_tiempo.activar();
    gestor_tiempo.tick(sf::milliseconds(40));
    EXPECT_EQ(gestor_tiempo.obtener_tiempo_juego().asMilliseconds(), 40);
}
TEST(Tiempo, GestorTiempoJuegoTickSinActivar) { //
    GestorTiempoJuego gestor_tiempo;
    gestor_tiempo.tick(sf::milliseconds(40));
    EXPECT_EQ(gestor_tiempo.obtener_tiempo_juego().asMilliseconds(), 0);
}
