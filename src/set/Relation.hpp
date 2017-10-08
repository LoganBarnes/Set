#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <mapbox/variant.hpp>

namespace set
{

template<typename T, std::size_t Level>
class Relation;

template<typename T>
class Relation<T, 0>
{
public:
    explicit Relation(glm::tvec3<T> point)
        : point_{std::make_shared<glm::tvec3<T>>(point)}
    {}

    const glm::tvec3<T> &get_point() const
    {
        return *point_;
    }

    void set_point(glm::tvec3<T> point)
    {
        *point_ = point;
    }
private:
    std::shared_ptr<glm::tvec3<T>> point_;
};

template<typename T, typename... Relations>
struct OptRel
{
    using variant = mapbox::util::variant<Relations...>;
    using next = OptRel<T, Relation<T, sizeof...(Relations)>, Relations...>;
};

template<typename T, std::size_t Level>
struct MakeOptRel
{
    using type = typename MakeOptRel<T, Level - 1>::type::next;
};

template<typename T>
struct MakeOptRel<T, 0>
{
    using type = OptRel<T, Relation<T, 0>>;
};

/** \brief The Relation< Relation< Ts > > class
 *
 * Represents all high order relations. Contains two lower level child relations (A and B).
*/
template<typename T, std::size_t Level>
class Relation
{
public:
    template<std::size_t LevelA, std::size_t LevelB>
    Relation(Relation<T, LevelA> a, Relation<T, LevelB> b)
        : a_(a), b_(b)
    {}

private:

    typename MakeOptRel<T, Level - 1>::type::variant a_;
    typename MakeOptRel<T, Level - 1>::type::variant b_;
};

template<typename T>
static auto make_relation(T x, T y, T z)
{
    return Relation<T, 0>{glm::tvec3<T>{x, y, z}};
}

template<typename T>
static auto make_relation(glm::tvec3<T> point)
{
    return Relation<T, 0>{point};
}

template<typename T, std::size_t LevelA, std::size_t LevelB>
auto make_relation(Relation<T, LevelA> a, Relation<T, LevelB> b)
{
    return Relation<T, std::max(LevelA, LevelB) + 1>(a, b);
}

} // namespace set
