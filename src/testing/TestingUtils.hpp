#pragma once

#include <glm/glm.hpp>

namespace test
{

void check_point(const glm::vec3 &expected, const glm::vec3 &actual);

void check_point(const glm::dvec3 &expected, const glm::dvec3 &actual);

}