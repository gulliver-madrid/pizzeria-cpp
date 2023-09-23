
#include "../juego.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Juego, EncargadasDelTipoConVectorVacio) {
    std::vector<EncargoACocina> encargadas;
    assert(encargadas.size() == 0);
    auto result = encargadas_del_tipo(encargadas, Margarita);
    EXPECT_EQ(result, 0);
}

TEST(Juego, EncargadasDelTipoConDosMargaritasYUnaPepperoni) {
    std::vector<EncargoACocina> encargadas;
    auto tp = TiempoPreparacion{Tiempo::CERO, Tiempo::CERO};
    encargadas.push_back(EncargoACocina{Margarita, tp});
    encargadas.push_back(EncargoACocina{Margarita, tp});
    encargadas.push_back(EncargoACocina{Pepperoni, tp});
    auto result = encargadas_del_tipo(encargadas, Margarita);
    EXPECT_EQ(result, 2);
    result = encargadas_del_tipo(encargadas, Pepperoni);
    EXPECT_EQ(result, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
