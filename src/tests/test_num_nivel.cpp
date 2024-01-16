#include "../shared_num_nivel.h"
#include <gtest/gtest.h>

TEST(NumNivelOpcional, SePuedeCrearSinArgumentos) { //
    const NumNivelOpcional num_nivel;
}

TEST(NumNivelOpcional, SePuedeCrearConArgumentos) { //
    const NumNivelOpcional num_nivel(1);
}

TEST(NumNivelOpcional, ToStringSinValorNumerico) { //
    const NumNivelOpcional num_nivel;
    ASSERT_EQ(num_nivel.to_string(), "-");
}

TEST(NumNivelOpcional, ToStringConValorNumerico) { //
    const NumNivelOpcional num_nivel(1);
    ASSERT_EQ(num_nivel.to_string(), "1");
}

TEST(NumNivelOpcional, ObtenerValorSinValorNumericoGeneraExcepcion) { //
    const NumNivelOpcional num_nivel;
    ASSERT_THROW(num_nivel.get_valor(), std::bad_optional_access);
}

TEST(NumNivelOpcional, ObtenerValorConValorNumerico) { //
    const NumNivelOpcional num_nivel(1);
    ASSERT_EQ(num_nivel.get_valor(), 1);
}

TEST(NumNivelOpcional, ManualTest) { //
    NumNivelOpcional num_nivel(1);
    NumNivelOpcional num_nivel_2(2);
    // SHOULD NOT COMPILE
    // num_nivel = num_nivel_2;
}
