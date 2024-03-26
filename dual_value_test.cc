#include "dual_value.h"

#include <cmath>

#include <gtest/gtest.h>

namespace maze {
namespace {

TEST(DualValueTest, EdgeValues) {
  EXPECT_TRUE(DualValue(2147483647,-2147483648) < DualValue(-2147483648, 2147483647));
}

TEST(DualValueTest, CloseEdgeValues) {
  EXPECT_TRUE(DualValue(2147483646,-2147483648) < DualValue(-2147483648, 2147483647));
}

TEST(MoreDualValueTest, FourAndMinusThree) {
  EXPECT_FALSE(DualValue(4, -3) > DualValue(0, 0));
}

TEST(MoreDualValueTest, MinusFourAndThree) {
  EXPECT_TRUE(DualValue(-4, 3) > DualValue(0, 0));
}

TEST(LessDualValueTest, FourAndMinusThree) {
  EXPECT_TRUE(DualValue(4, -3) < DualValue(0, 0));
}

TEST(LessDualValueTest, MinusFourAndThree) {
  EXPECT_FALSE(DualValue(-4, 3) < DualValue(0, 0));
}

TEST(EqualDualValueTest, Equal) {
  EXPECT_TRUE(DualValue(-4, 3) == DualValue(-4, 3));
}

TEST(EqualDualValueTest, NotEqual) {
  EXPECT_FALSE(DualValue(4, -3) == DualValue(-4, 3));
}

TEST(EqualDualValueTest, NotEqualA) {
  EXPECT_FALSE(DualValue(-4, -3) == DualValue(4, -3));
}

TEST(EqualDualValueTest, NotEqualB) {
  EXPECT_FALSE(DualValue(4, -3) == DualValue(4, 3));
}

TEST(NotEqualDualValueTest, Equal) {
  EXPECT_FALSE(DualValue(-4, 3) != DualValue(-4, 3));
}

TEST(NotEqualDualValueTest, NotEqual) {
  EXPECT_TRUE(DualValue(4, -3) != DualValue(-4, 3));
}

TEST(NotEqualDualValueTest, NotEqualA) {
  EXPECT_TRUE(DualValue(-4, -3) != DualValue(4, -3));
}

TEST(NotEqualDualValueTest, NotEqualB) {
  EXPECT_TRUE(DualValue(4, -3) != DualValue(4, 3));
}

TEST(DualValueTest, Comparison) {
  for (int i = -10000; i <= 10000; ++i) {
    for (int j = -10000; j <= 10000; ++j) {
      EXPECT_EQ(DualValue(i, j) <=> DualValue(0, 0), i + sqrt(2) * j <=> 0.0);
    }
  }
}

TEST(DualValueTest, Sum) {
  EXPECT_EQ(DualValue(-1, 2) + DualValue(4, -7), DualValue(3, -5));
}

} // namespace
} // namespace maze
