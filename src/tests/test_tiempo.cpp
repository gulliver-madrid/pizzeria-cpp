
#include "../juego_assert.h"
#include "../tiempo.h"

#include <gtest/gtest.h>

TEST(Tiempo, TimerNoIniciadoGeneraExcepcionAlTerminarlo) { //
    Timer t;
#ifdef _DEBUG
    EXPECT_THROW(t.termino(), JuegoException);
#else
    EXPECT_THROW(t.termino(), std::bad_optional_access);
#endif
}
