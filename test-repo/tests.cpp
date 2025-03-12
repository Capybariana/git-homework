#include <gtest/gtest.h>
#include "candle.h"

// 2.1 body_contains
TEST(CandleTest, BodyContains_GreenCandle_InsideBody) {
    Candle c(100, 110, 90, 105);
    EXPECT_TRUE(c.body_contains(102));
}

TEST(CandleTest, BodyContains_RedCandle_InsideBody) {
    Candle c(105, 110, 90, 100);
    EXPECT_TRUE(c.body_contains(102));
}

TEST(CandleTest, BodyContains_BoundaryCondition) {
    Candle c(100, 110, 90, 105);
    EXPECT_TRUE(c.body_contains(100)); // граница
    EXPECT_FALSE(c.body_contains(99)); // за пределами
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}