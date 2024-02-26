#include "../shared/num_nivel.h"
#include <gtest/gtest.h>

// NumNivel

TEST(NumNivel, CrearValorSinValorNumericoGeneraExcepcion) { //
    ASSERT_THROW(NumNivel(0), std::invalid_argument);
}

TEST(NumNivel, ObtenerValorConValorNumerico) { //
    const NumNivel num_nivel(1);
    ASSERT_EQ(num_nivel.get_valor(), 1);
}

// NumNivelOpcional

TEST(NumNivelOpcional, SePuedeCrearSinArgumentos) { //
    const NumNivelOpcional num_nivel;
}

TEST(NumNivelOpcional, SePuedeCrearConArgumentos) { //
    const NumNivelOpcional num_nivel(1);
}

TEST(NumNivelOpcional, ToStringSinValorNumerico) { //
    const NumNivelOpcional num_nivel;
    ASSERT_EQ(to_string(num_nivel), "-");
}

TEST(NumNivelOpcional, ToStringConValorNumerico) { //
    const NumNivelOpcional num_nivel(1);
    ASSERT_EQ(to_string(num_nivel), "1");
}
