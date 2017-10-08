// Geometry.hpp
#pragma once


#include <vector>
#include <glm/glm.hpp>


namespace set
{

template<int Level, typename ... Ts>
class Relation;

class Geometry
{

public:

    Geometry() = default;
    virtual ~Geometry() = default;

    virtual std::vector<glm::vec3> getBasePoints() const = 0;


    virtual glm::vec3 &getPoint() = 0;

    virtual Geometry &getA() = 0;
    virtual Geometry &getB() = 0;
};

} // namespace set
