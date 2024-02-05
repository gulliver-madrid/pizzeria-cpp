
#include "../tiempo.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Tiempo, RestarTiempo) { //
    const sf::Time t1 = sf::milliseconds(1);
    const sf::Time t2 = sf::milliseconds(3);
    EXPECT_EQ(t2 - t1, sf::milliseconds(2));
}
TEST(Tiempo, GestorTiempoJuegoTick) { //
    GestorTiempoJuego gtj;
    gtj.activar();
    gtj.tick(sf::milliseconds(40));
    EXPECT_EQ(gtj.obtener_tiempo_transcurrido().asMilliseconds(), 40);
}
TEST(Tiempo, GestorTiempoJuegoTickSinActivar) { //
    GestorTiempoJuego gtj;
    gtj.tick(sf::milliseconds(40));
    EXPECT_EQ(gtj.obtener_tiempo_transcurrido().asMilliseconds(), 0);
}
