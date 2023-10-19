
#include "../tiempo.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Tiempo, RestarTiempo) { //
    const Tiempo t1 = Tiempo::desde_milisegundos(1);
    const Tiempo t2 = Tiempo::desde_milisegundos(3);
    EXPECT_EQ(t2 - t1, Tiempo::desde_milisegundos(2));
}
