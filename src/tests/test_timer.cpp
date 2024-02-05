#include "../tiempo.h"
#include <gtest/gtest.h>

#ifdef _DEBUG
#include "../juego_assert.h"
#define EXCEPCION JuegoException
#else
#define EXCEPCION std::bad_optional_access
#endif

TEST(GestorTimer, GestorTimerNoIniciadoGeneraExcepcionAlTerminarlo) { //
    GestorTimer t;
    EXPECT_THROW(t.termino(), EXCEPCION);
}
