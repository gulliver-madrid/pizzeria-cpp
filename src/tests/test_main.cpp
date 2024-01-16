#include "../shared/log_init.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    init_log();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
