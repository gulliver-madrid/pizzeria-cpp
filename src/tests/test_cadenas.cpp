
#include "../vista/cadenas.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(Cadenas, Interpolar) { //
    EXPECT_EQ(interpolar_unicode("%a"), A_ACUTE);
    EXPECT_EQ(
        interpolar_unicode("%a%e%i%o%u"),
        std::string(A_ACUTE) + E_ACUTE + I_ACUTE + O_ACUTE + U_ACUTE
    );
    EXPECT_EQ(
        interpolar_unicode("%n%!!%??"),
        std::string(N_TILDE) + START_EXCLAMATION + "!" + START_QUESTION + "?"
    );
}

TEST(Cadenas, UnirCadenas) { //
    EXPECT_EQ(unir_cadenas({"hola", "mundo"}, " "), "hola mundo");
}
