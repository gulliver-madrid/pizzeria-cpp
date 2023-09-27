
#include "../modelo/modelo.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Juego, EncargadasDelTipoConVectorVacio) {
    Encargos encargos;
    assert(encargos.datos.empty());
    auto result = encargos.del_tipo(TipoPizza::Margarita);
    EXPECT_EQ(result, 0);
}

TEST(Juego, EncargadasDelTipoConDosMargaritasYUnaPepperoni) {
    // El TiempoPreparacion deberia ser irrelevante aqui
    auto tp = TiempoPreparacion{Tiempo::CERO, Tiempo::CERO};

    Encargos encargos;
    encargos.datos.push_back(EncargoACocina{TipoPizza::Margarita, tp});
    encargos.datos.push_back(EncargoACocina{TipoPizza::Margarita, tp});
    encargos.datos.push_back(EncargoACocina{TipoPizza::Pepperoni, tp});

    EXPECT_EQ(                                   //
        encargos.del_tipo(TipoPizza::Margarita), //
        2
    );
    EXPECT_EQ(                                   //
        encargos.del_tipo(TipoPizza::Pepperoni), //
        1
    );
}
