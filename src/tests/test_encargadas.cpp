
#include "../modelo/modelo.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Juego, EncargadasDelTipoConVectorVacio) {
    std::vector<EncargoACocina> encargadas;
    assert(encargadas.size() == 0);
    auto result = encargadas_del_tipo(encargadas, TipoPizza::Margarita);
    EXPECT_EQ(result, 0);
}

TEST(Juego, EncargadasDelTipoConDosMargaritasYUnaPepperoni) {
    // El TiempoPreparacion deberia ser irrelevante aqui
    auto tp = TiempoPreparacion{Tiempo::CERO, Tiempo::CERO};

    std::vector<EncargoACocina> encargadas;
    encargadas.push_back(EncargoACocina{TipoPizza::Margarita, tp});
    encargadas.push_back(EncargoACocina{TipoPizza::Margarita, tp});
    encargadas.push_back(EncargoACocina{TipoPizza::Pepperoni, tp});

    EXPECT_EQ(                                                 //
        encargadas_del_tipo(encargadas, TipoPizza::Margarita), //
        2
    );
    EXPECT_EQ(                                                 //
        encargadas_del_tipo(encargadas, TipoPizza::Pepperoni), //
        1
    );
}
