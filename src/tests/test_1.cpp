#include <gtest/gtest.h>

TEST(ComponentesTest, Funcion1) { EXPECT_EQ((1 + 1), 2); }
TEST(ComponentesTest, Funcion2) { EXPECT_EQ((1 + 1), 3); }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
