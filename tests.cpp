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

// 2.2 contains
TEST(CandleTest, Contains_InsideCandle) {
    Candle c(100, 110, 90, 105);
    EXPECT_TRUE(c.contains(95));
}

TEST(CandleTest, Contains_OnBoundary) {
    Candle c(100, 110, 90, 105);
    EXPECT_TRUE(c.contains(90));
    EXPECT_TRUE(c.contains(110));
}

TEST(CandleTest, Contains_OutsideCandle) {
    Candle c(100, 110, 90, 105);
    EXPECT_FALSE(c.contains(89));
    EXPECT_FALSE(c.contains(111));
}
// 2.3 full_size
TEST(CandleTest, FullSize_NormalCase) {
    Candle c(100, 110, 90, 105);
    EXPECT_DOUBLE_EQ(c.full_size(), 20);
}

TEST(CandleTest, FullSize_ZeroSize) {
    Candle c(100, 100, 100, 100);
    EXPECT_DOUBLE_EQ(c.full_size(), 0);
}

TEST(CandleTest, FullSize_NegativePrices) {
    Candle c(-100, -90, -110, -95);
    EXPECT_DOUBLE_EQ(c.full_size(), 20);
}

// 2.4 body_size
TEST(CandleTest, BodySize_GreenCandle) {
    Candle c(100, 110, 90, 105);
    EXPECT_DOUBLE_EQ(c.body_size(), 5);
}

TEST(CandleTest, BodySize_RedCandle) {
    Candle c(105, 110, 90, 100);
    EXPECT_DOUBLE_EQ(c.body_size(), 5);
}

TEST(CandleTest, BodySize_ZeroBody) {
    Candle c(100, 110, 90, 100);
    EXPECT_DOUBLE_EQ(c.body_size(), 0);
}
// 2.5 is_red
TEST(CandleTest, IsRed_TrueCase) {
    Candle c(105, 110, 90, 100);
    EXPECT_TRUE(c.is_red());
}

TEST(CandleTest, IsRed_FalseCase) {
    Candle c(100, 110, 90, 105);
    EXPECT_FALSE(c.is_red());
}

TEST(CandleTest, IsRed_EqualOpenClose) {
    Candle c(100, 110, 90, 100);
    EXPECT_FALSE(c.is_red());
}
// 2.6 is_green
TEST(CandleTest, IsGreen_TrueCase) {
    Candle c(100, 110, 90, 105);
    EXPECT_TRUE(c.is_green());
}

TEST(CandleTest, IsGreen_FalseCase) {
    Candle c(105, 110, 90, 100);
    EXPECT_FALSE(c.is_green());
}

TEST(CandleTest, IsGreen_EqualOpenClose) {
    Candle c(100, 110, 90, 100);
    EXPECT_FALSE(c.is_green());
}

TEST(SimpleMathTest, OneplusOneEqualsTwo){
    EXPECT_EQ(1 + 1, 2);
}

TEST(SimpleMathTest, OneplusTwoEqualsThree){
    EXPECT_EQ(1 + 2, 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}