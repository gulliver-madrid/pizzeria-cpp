
#include "../modelo/encargos.h"
#include "../modelo/modelo.h"
#include <cassert>
#include <gtest/gtest.h>

using modelo::TipoPizza;

TEST(Encargadas, EncargadasDelTipoConVectorVacio) {
    Encargos encargos;
    EXPECT_EQ(encargos.total(), 0);
    auto result = encargos.del_tipo(TipoPizza::Margarita);
    EXPECT_EQ(result, 0);
}

TEST(Encargadas, EncargadasDelTipoConDosMargaritasYUnaPepperoni) {
    Encargos encargos;
    encargos.anadir(EncargoACocina(TipoPizza::Margarita, TiempoJuego_CERO));
    encargos.anadir(EncargoACocina(TipoPizza::Margarita, TiempoJuego_CERO));
    encargos.anadir(EncargoACocina(TipoPizza::Pepperoni, TiempoJuego_CERO));

    EXPECT_EQ(
        encargos.del_tipo(TipoPizza::Margarita), //
        2                                        //
    );
    EXPECT_EQ(
        encargos.del_tipo(TipoPizza::Pepperoni), //
        1                                        //
    );
}
