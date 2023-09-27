
#include "../modelo/modelo.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Juego, EncargadasDelTipoConVectorVacio) {
    Encargos encargos;
    EXPECT_EQ(encargos.total(), 0);
    auto result = encargos.del_tipo(TipoPizza::Margarita);
    EXPECT_EQ(result, 0);
}

TEST(Juego, EncargadasDelTipoConDosMargaritasYUnaPepperoni) {
    // El TiempoPreparacion deberia ser irrelevante aqui
    auto tp = TiempoPreparacion{Tiempo::CERO, Tiempo::CERO};

    Encargos encargos;
    encargos.anadir(EncargoACocina{TipoPizza::Margarita, tp});
    encargos.anadir(EncargoACocina{TipoPizza::Margarita, tp});
    encargos.anadir(EncargoACocina{TipoPizza::Pepperoni, tp});

    EXPECT_EQ(                                   //
        encargos.del_tipo(TipoPizza::Margarita), //
        2
    );
    EXPECT_EQ(                                   //
        encargos.del_tipo(TipoPizza::Pepperoni), //
        1
    );
}
