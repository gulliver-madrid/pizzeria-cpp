#include "../juego_assert.h"
#include "../tiempo.h"

#include <gtest/gtest.h>

#ifdef _DEBUG
#define EXCEPCION JuegoException
#else
#define EXCEPCION std::bad_optional_access
#endif

TEST(Tiempo, TimerNoIniciadoGeneraExcepcionAlTerminarlo) { //
    Timer t;
    EXPECT_THROW(t.termino(), EXCEPCION);
}
