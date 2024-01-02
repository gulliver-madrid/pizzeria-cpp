
#include "../../modelo/encargos.h"
#include "../../modelo/modelo.h"
#include <cassert>
#include <gtest/gtest.h>

using dominio::TipoPizza;

// Tests de la struct Encargos

TEST(Encargadas, EncargadasDelTipoConVectorVacio) {
    Encargos encargos;
    EXPECT_EQ(encargos.total(), 0);
    auto result = encargos.del_tipo(TipoPizza::Margarita);
    EXPECT_EQ(result, 0);
}

TEST(Encargadas, EncargadasDelTipoConDosMargaritasYUnaPepperoni) {
    Encargos encargos;
    EncargoACocina data[] = {
        {TipoPizza::Margarita},
        {TipoPizza::Margarita},
        {TipoPizza::Pepperoni},
    };
    for (const auto &encargo : data) {
        encargos.anadir(encargo);
    }
    EXPECT_EQ(
        encargos.del_tipo(TipoPizza::Margarita), //
        2                                        //
    );
    EXPECT_EQ(
        encargos.del_tipo(TipoPizza::Pepperoni), //
        1                                        //
    );
}
