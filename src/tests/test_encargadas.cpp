
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
    // El TiempoPreparacion deberia ser irrelevante aqui
    auto tp = TiempoPreparacion{Tiempo::CERO, Tiempo::CERO};

    std::vector<EncargoACocina> encargadas;
    encargadas.push_back(EncargoACocina{Margarita, tp});
    encargadas.push_back(EncargoACocina{Margarita, tp});
    encargadas.push_back(EncargoACocina{Pepperoni, tp});

    EXPECT_EQ(                                      //
        encargadas_del_tipo(encargadas, Margarita), //
        2
    );
    EXPECT_EQ(                                      //
        encargadas_del_tipo(encargadas, Pepperoni), //
        1
    );
}
