#include <set/Relation.hpp>
#include <testing/TestingUtils.hpp>
#include <gtest/gtest.h>

namespace
{

template<typename T>
class RelationUnitTests: public ::testing::Test
{
};

typedef ::testing::Types<float, double> Types;

TYPED_TEST_CASE(RelationUnitTests, Types);

TYPED_TEST(RelationUnitTests, TemplatesCompileSameTypes)
{
    // points
    auto p1 = set::make_relation(TypeParam(0), TypeParam(0), TypeParam(0));
    auto p2 = set::make_relation(TypeParam(1), TypeParam(0), TypeParam(0));
    auto p3 = set::make_relation(TypeParam(0), TypeParam(1), TypeParam(0));

    auto p4 = set::make_relation(TypeParam(0), TypeParam(0), TypeParam(1));
    auto p5 = set::make_relation(TypeParam(1), TypeParam(0), TypeParam(1));
    auto p6 = set::make_relation(TypeParam(0), TypeParam(1), TypeParam(1));

    auto p7 = set::make_relation(TypeParam(0), TypeParam(0), TypeParam(2));
    auto p8 = set::make_relation(TypeParam(1), TypeParam(0), TypeParam(2));
    auto p9 = set::make_relation(TypeParam(0), TypeParam(1), TypeParam(2));

    // lines
    auto l1 = set::make_relation(p1, p2);
    auto l2 = set::make_relation(p1, p3);

    auto l3 = set::make_relation(p4, p5);
    auto l4 = set::make_relation(p4, p6);

    auto l5 = set::make_relation(p7, p8);
    auto l6 = set::make_relation(p7, p9);

    // planes
    auto t1 = set::make_relation(l1, l2);
    auto t2 = set::make_relation(l3, l4);
    auto t3 = set::make_relation(l5, l6);

    // volume
    auto v1 = set::make_relation(t1, t2);
    auto v2 = set::make_relation(t2, t3);

    // temporal volume
    set::make_relation(v1, v2);
}

TYPED_TEST(RelationUnitTests, TemplatesCompileDifferentTypes)
{
    auto p1 = set::make_relation(TypeParam(0), TypeParam(0), TypeParam(0));
    auto p2 = set::make_relation(TypeParam(1), TypeParam(0), TypeParam(0));
    auto p3 = set::make_relation(TypeParam(0), TypeParam(1), TypeParam(0));
    auto p4 = set::make_relation(TypeParam(1), TypeParam(1), TypeParam(0));

    auto l1 = set::make_relation(p1, p2);
    auto l2 = set::make_relation(p3, p4);

    auto lp1 = set::make_relation(l1, p3);
    auto lp2 = set::make_relation(l1, p4);

    auto pl1 = set::make_relation(p1, l2);
    auto pl2 = set::make_relation(p2, l2);
}

TYPED_TEST(RelationUnitTests, TemplatesCompileSameTypes2)
{
    // points
    auto p1 = set::make_relation(TypeParam(0), TypeParam(0), TypeParam(0));
    auto p2 = set::make_relation(TypeParam(1), TypeParam(0), TypeParam(0));
    auto p3 = set::make_relation(TypeParam(0), TypeParam(1), TypeParam(0));

    auto p4 = set::make_relation(TypeParam(0), TypeParam(0), TypeParam(1));
    auto p5 = set::make_relation(TypeParam(1), TypeParam(0), TypeParam(1));
    auto p6 = set::make_relation(TypeParam(0), TypeParam(1), TypeParam(1));

    auto p7 = set::make_relation(TypeParam(0), TypeParam(0), TypeParam(2));
    auto p8 = set::make_relation(TypeParam(1), TypeParam(0), TypeParam(2));
    auto p9 = set::make_relation(TypeParam(0), TypeParam(1), TypeParam(2));

    test::check_point(glm::tvec3<TypeParam>{0, 0, 0}, p1.get_point());
    test::check_point(glm::tvec3<TypeParam>{1, 0, 0}, p2.get_point());
    test::check_point(glm::tvec3<TypeParam>{0, 1, 0}, p3.get_point());

    test::check_point(glm::tvec3<TypeParam>{0, 0, 1}, p4.get_point());
    test::check_point(glm::tvec3<TypeParam>{1, 0, 1}, p5.get_point());
    test::check_point(glm::tvec3<TypeParam>{0, 1, 1}, p6.get_point());

    test::check_point(glm::tvec3<TypeParam>{0, 0, 2}, p7.get_point());
    test::check_point(glm::tvec3<TypeParam>{1, 0, 2}, p8.get_point());
    test::check_point(glm::tvec3<TypeParam>{0, 1, 2}, p9.get_point());
}

//
///////////////////////////////////////////////////////////////////
///// \brief BasePointsAreCorrect
///////////////////////////////////////////////////////////////////
//TEST_F(RelationUnitTests, BasePointsAreCorrect)
//{
//    glm::vec3 gp1 = {0.0f, 0.0f, 0.0f};
//    glm::vec3 gp2 = {1.0f, 0.0f, 0.0f};
//    glm::vec3 gp3 = {0.0f, 1.0f, 0.0f};
//
//    glm::vec3 gp4 = {0.0f, 0.0f, 1.0f};
//    glm::vec3 gp5 = {1.0f, 0.0f, 1.0f};
//    glm::vec3 gp6 = {0.0f, 1.0f, 1.0f};
//
//    glm::vec3 gp7 = {0.0f, 0.0f, 2.0f};
//    glm::vec3 gp8 = {1.0f, 0.0f, 2.0f};
//    glm::vec3 gp9 = {0.0f, 1.0f, 2.0f};
//
//    // points
//    auto p1 = set::make_relation(gp1.x, gp1.y, gp1.z);
//    auto p2 = set::make_relation(gp2.x, gp2.y, gp2.z);
//    auto p3 = set::make_relation(gp3.x, gp3.y, gp3.z);
//
//    auto p4 = set::make_relation(gp4.x, gp4.y, gp4.z);
//    auto p5 = set::make_relation(gp5.x, gp5.y, gp5.z);
//    auto p6 = set::make_relation(gp6.x, gp6.y, gp6.z);
//
//    auto p7 = set::make_relation(gp7.x, gp7.y, gp7.z);
//    auto p8 = set::make_relation(gp8.x, gp8.y, gp8.z);
//    auto p9 = set::make_relation(gp9.x, gp9.y, gp9.z);
//
//    checkPoints(std::vector<glm::vec3>{gp1}, p1.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp2}, p2.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp3}, p3.getBasePoints());
//
//    checkPoints(std::vector<glm::vec3>{gp4}, p4.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp5}, p5.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp6}, p6.getBasePoints());
//
//    checkPoints(std::vector<glm::vec3>{gp7}, p7.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp8}, p8.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp9}, p9.getBasePoints());
//
//
//    // lines
//    auto l1 = set::make_relation(p1, p2);
//    auto l2 = set::make_relation(p1, p3);
//
//    auto l3 = set::make_relation(p4, p5);
//    auto l4 = set::make_relation(p4, p6);
//
//    auto l5 = set::make_relation(p7, p8);
//    auto l6 = set::make_relation(p7, p9);
//
//    checkPoints(std::vector<glm::vec3>{gp1, gp2}, l1.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp1, gp3}, l2.getBasePoints());
//
//    checkPoints(std::vector<glm::vec3>{gp4, gp5}, l3.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp4, gp6}, l4.getBasePoints());
//
//    checkPoints(std::vector<glm::vec3>{gp7, gp8}, l5.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp7, gp9}, l6.getBasePoints());
//
//
//    // planes
//    auto t1 = set::make_relation(l1, l2);
//
//    auto t2 = set::make_relation(l3, l4);
//
//    auto t3 = set::make_relation(l5, l6);
//
//    checkPoints(std::vector<glm::vec3>{gp1, gp2, gp1, gp3}, t1.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp4, gp5, gp4, gp6}, t2.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp7, gp8, gp7, gp9}, t3.getBasePoints());
//
//
//    // volume
//    auto v1 = set::make_relation(t1, t2);
//
//    auto v2 = set::make_relation(t2, t3);
//
//    checkPoints(std::vector<glm::vec3>{gp1, gp2, gp1, gp3,
//                                       gp4, gp5, gp4, gp6}, v1.getBasePoints());
//    checkPoints(std::vector<glm::vec3>{gp4, gp5, gp4, gp6,
//                                       gp7, gp8, gp7, gp9}, v2.getBasePoints());
//
//
//    // temporal volume
//    auto tv1 = set::make_relation(v1, v2);
//
//    checkPoints(std::vector<glm::vec3>{gp1, gp2, gp1, gp3,
//                                       gp4, gp5, gp4, gp6,
//                                       gp4, gp5, gp4, gp6,
//                                       gp7, gp8, gp7, gp9}, tv1.getBasePoints());
//}
//
//
//
///////////////////////////////////////////////////////////////////
///// \brief LevelsAreCorrect
///////////////////////////////////////////////////////////////////
//TEST_F(RelationUnitTests, LevelsAreCorrect)
//{
//    // points
//    auto p1 = set::make_relation(0.0f, 0.0f, 0.0f);
//    auto p2 = set::make_relation(1.0f, 0.0f, 0.0f);
//    auto p3 = set::make_relation(0.0f, 1.0f, 0.0f);
//
//    auto p4 = set::make_relation(0.0f, 0.0f, 1.0f);
//    auto p5 = set::make_relation(1.0f, 0.0f, 1.0f);
//    auto p6 = set::make_relation(0.0f, 1.0f, 1.0f);
//
//    auto p7 = set::make_relation(0.0f, 0.0f, 2.0f);
//    auto p8 = set::make_relation(1.0f, 0.0f, 2.0f);
//    auto p9 = set::make_relation(0.0f, 1.0f, 2.0f);
//
//    ASSERT_EQ(0, p1.getRelationLevel());
//    ASSERT_EQ(0, p2.getRelationLevel());
//    ASSERT_EQ(0, p3.getRelationLevel());
//
//    ASSERT_EQ(0, p4.getRelationLevel());
//    ASSERT_EQ(0, p5.getRelationLevel());
//    ASSERT_EQ(0, p6.getRelationLevel());
//
//    ASSERT_EQ(0, p7.getRelationLevel());
//    ASSERT_EQ(0, p8.getRelationLevel());
//    ASSERT_EQ(0, p9.getRelationLevel());
//
//
//    // lines
//    auto l1 = set::make_relation(p1, p2);
//    auto l2 = set::make_relation(p1, p3);
//
//    auto l3 = set::make_relation(p4, p5);
//    auto l4 = set::make_relation(p4, p6);
//
//    auto l5 = set::make_relation(p7, p8);
//    auto l6 = set::make_relation(p7, p9);
//
//    ASSERT_EQ(1, l1.getRelationLevel());
//    ASSERT_EQ(1, l2.getRelationLevel());
//
//    ASSERT_EQ(1, l3.getRelationLevel());
//    ASSERT_EQ(1, l4.getRelationLevel());
//
//    ASSERT_EQ(1, l5.getRelationLevel());
//    ASSERT_EQ(1, l6.getRelationLevel());
//
//
//    // planes
//    auto t1 = set::make_relation(l1, l2);
//
//    auto t2 = set::make_relation(l3, l4);
//
//    auto t3 = set::make_relation(l5, l6);
//
//    ASSERT_EQ(2, t1.getRelationLevel());
//    ASSERT_EQ(2, t2.getRelationLevel());
//    ASSERT_EQ(2, t3.getRelationLevel());
//
//
//    // volume
//    auto v1 = set::make_relation(t1, t2);
//
//    auto v2 = set::make_relation(t2, t3);
//
//    ASSERT_EQ(3, v1.getRelationLevel());
//    ASSERT_EQ(3, v2.getRelationLevel());
//
//
//    // temporal volume
//    auto tv1 = set::make_relation(v1, v2);
//
//    ASSERT_EQ(4, tv1.getRelationLevel());
//}

} // namespace
