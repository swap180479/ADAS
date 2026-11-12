#include "aeb_controller.h"

#include <cmath>
#include <limits>
#include <gtest/gtest.h>

TEST(AebController, TC001_NotClosing) {
    AebDecision result{};
    EXPECT_EQ(aeb_evaluate(20.0, 0.0, &result), AEB_OK);
    EXPECT_EQ(result.brake_request, 0);
    EXPECT_TRUE(std::isinf(result.ttc_s));
}

TEST(AebController, TC002_AboveThreshold) {
    AebDecision result{};
    ASSERT_EQ(aeb_evaluate(30.0, 10.0, &result), AEB_OK);
    EXPECT_EQ(result.brake_request, 0);
    EXPECT_DOUBLE_EQ(result.ttc_s, 3.0);
}

TEST(AebController, TC003_AtThreshold) {
    AebDecision result{};
    ASSERT_EQ(aeb_evaluate(20.0, 10.0, &result), AEB_OK);
    EXPECT_EQ(result.brake_request, 1);
    EXPECT_DOUBLE_EQ(result.ttc_s, 2.0);
}

TEST(AebController, TC004_BelowThreshold) {
    AebDecision result{};
    ASSERT_EQ(aeb_evaluate(10.0, 10.0, &result), AEB_OK);
    EXPECT_EQ(result.brake_request, 1);
    EXPECT_DOUBLE_EQ(result.ttc_s, 1.0);
}

TEST(AebController, TC005_ZeroDistance) {
    AebDecision result{};
    ASSERT_EQ(aeb_evaluate(0.0, 10.0, &result), AEB_OK);
    EXPECT_EQ(result.brake_request, 1);
    EXPECT_DOUBLE_EQ(result.ttc_s, 0.0);
}

TEST(AebController, TC006_NegativeDistance) {
    AebDecision result{1, 0.0};
    EXPECT_EQ(aeb_evaluate(-1.0, 10.0, &result), AEB_INVALID_INPUT);
    EXPECT_EQ(result.brake_request, 0);
    EXPECT_TRUE(std::isinf(result.ttc_s));
}

TEST(AebController, TC007_NegativeClosingSpeed) {
    AebDecision result{1, 0.0};
    EXPECT_EQ(aeb_evaluate(10.0, -1.0, &result), AEB_INVALID_INPUT);
    EXPECT_EQ(result.brake_request, 0);
    EXPECT_TRUE(std::isinf(result.ttc_s));
}

TEST(AebController, TC008_NaNDistance) {
    AebDecision result{1, 0.0};
    EXPECT_EQ(aeb_evaluate(std::numeric_limits<double>::quiet_NaN(), 10.0, &result),
              AEB_INVALID_INPUT);
    EXPECT_EQ(result.brake_request, 0);
    EXPECT_TRUE(std::isinf(result.ttc_s));
}

TEST(AebController, TC009_NullOutput) {
    EXPECT_EQ(aeb_evaluate(10.0, 10.0, nullptr), AEB_INVALID_INPUT);
}
