#include "TestingUtils.hpp"
#include <gtest/gtest.h>

namespace test
{

void check_point(const glm::vec3 &expected, const glm::vec3 &actual)
{
    EXPECT_FLOAT_EQ(actual.x, expected.x);
    EXPECT_FLOAT_EQ(actual.y, expected.y);
    EXPECT_FLOAT_EQ(actual.z, expected.z);
}

void check_point(const glm::dvec3 &expected, const glm::dvec3 &actual)
{
    EXPECT_DOUBLE_EQ(actual.x, expected.x);
    EXPECT_DOUBLE_EQ(actual.y, expected.y);
    EXPECT_DOUBLE_EQ(actual.z, expected.z);
}

} // namespace test