#include "Relation.hpp"
#include "RelationDispatcher.hpp"
#include "gmock/gmock.h"


namespace
{

constexpr float eps = 1.0e-7f;


///
/// \brief The RelationUnitTests class
///
class RelationUnitTests : public ::testing::Test
{

protected:

  /////////////////////////////////////////////////////////////////
  /// \brief RelationUnitTests
  /////////////////////////////////////////////////////////////////
  RelationUnitTests( )
  {}


  /////////////////////////////////////////////////////////////////
  /// \brief ~RelationUnitTests
  /////////////////////////////////////////////////////////////////
  virtual
  ~RelationUnitTests( )
  {}



  /////////////////////////////////////////////////////////////////
  /// \brief checkPoint
  /// \param expected
  /// \param actual
  /////////////////////////////////////////////////////////////////
  static
  void
  checkPoint(
             const glm::vec3 &expected,
             const glm::vec3 &actual
             )
  {
    ASSERT_NEAR( expected.x, actual.x, eps );
    ASSERT_NEAR( expected.y, actual.y, eps );
    ASSERT_NEAR( expected.z, actual.z, eps );
  }


  /////////////////////////////////////////////////////////////////
  /// \brief checkPoints
  /// \param expected
  /// \param actual
  /////////////////////////////////////////////////////////////////
  static
  void
  checkPoints(
              const std::vector< glm::vec3 > &expected,
              const std::vector< glm::vec3 > &actual
              )
  {
    ASSERT_EQ( expected.size( ), actual.size( ) ) << "glm::vec3 vectors are not the same size";

    for ( int i = 0; i < expected.size( ); ++i )
    {
      checkPoint( expected[ i ], actual[ i ] );
    }
  }


};



/////////////////////////////////////////////////////////////////
/// \brief TemplatesCompile
/////////////////////////////////////////////////////////////////
TEST_F( RelationUnitTests, TemplatesCompile )
{
  // points
  auto p1 = set::make_relation( 0.0f, 0.0f, 0.0f );
  auto p2 = set::make_relation( 1.0f, 0.0f, 0.0f );
  auto p3 = set::make_relation( 0.0f, 1.0f, 0.0f );

  auto p4 = set::make_relation( 0.0f, 0.0f, 1.0f );
  auto p5 = set::make_relation( 1.0f, 0.0f, 1.0f );
  auto p6 = set::make_relation( 0.0f, 1.0f, 1.0f );

  auto p7 = set::make_relation( 0.0f, 0.0f, 2.0f );
  auto p8 = set::make_relation( 1.0f, 0.0f, 2.0f );
  auto p9 = set::make_relation( 0.0f, 1.0f, 2.0f );

  // lines
  auto l1 = set::make_relation( p1, p2 );
  auto l2 = set::make_relation( p1, p3 );

  auto l3 = set::make_relation( p4, p5 );
  auto l4 = set::make_relation( p4, p6 );

  auto l5 = set::make_relation( p7, p8 );
  auto l6 = set::make_relation( p7, p9 );

  // planes
  auto t1 = set::make_relation( l1, l2 );

  auto t2 = set::make_relation( l3, l4 );

  auto t3 = set::make_relation( l5, l6 );

  // volume
  auto v1 = set::make_relation( t1, t2 );

  auto v2 = set::make_relation( t2, t3 );

  // temporal volume
  set::make_relation( v1, v2 );
}


/////////////////////////////////////////////////////////////////
/// \brief BasePointsAreCorrect
/////////////////////////////////////////////////////////////////
TEST_F( RelationUnitTests, BasePointsAreCorrect )
{
  glm::vec3 gp1 = { 0.0f, 0.0f, 0.0f };
  glm::vec3 gp2 = { 1.0f, 0.0f, 0.0f };
  glm::vec3 gp3 = { 0.0f, 1.0f, 0.0f };

  glm::vec3 gp4 = { 0.0f, 0.0f, 1.0f };
  glm::vec3 gp5 = { 1.0f, 0.0f, 1.0f };
  glm::vec3 gp6 = { 0.0f, 1.0f, 1.0f };

  glm::vec3 gp7 = { 0.0f, 0.0f, 2.0f };
  glm::vec3 gp8 = { 1.0f, 0.0f, 2.0f };
  glm::vec3 gp9 = { 0.0f, 1.0f, 2.0f };

  // points
  auto p1 = set::make_relation( gp1.x, gp1.y, gp1.z );
  auto p2 = set::make_relation( gp2.x, gp2.y, gp2.z );
  auto p3 = set::make_relation( gp3.x, gp3.y, gp3.z );

  auto p4 = set::make_relation( gp4.x, gp4.y, gp4.z );
  auto p5 = set::make_relation( gp5.x, gp5.y, gp5.z );
  auto p6 = set::make_relation( gp6.x, gp6.y, gp6.z );

  auto p7 = set::make_relation( gp7.x, gp7.y, gp7.z );
  auto p8 = set::make_relation( gp8.x, gp8.y, gp8.z );
  auto p9 = set::make_relation( gp9.x, gp9.y, gp9.z );

  checkPoints( std::vector< glm::vec3 >{ gp1 }, p1.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp2 }, p2.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp3 }, p3.getBasePoints( ) );

  checkPoints( std::vector< glm::vec3 >{ gp4 }, p4.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp5 }, p5.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp6 }, p6.getBasePoints( ) );

  checkPoints( std::vector< glm::vec3 >{ gp7 }, p7.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp8 }, p8.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp9 }, p9.getBasePoints( ) );


  // lines
  auto l1 = set::make_relation( p1, p2 );
  auto l2 = set::make_relation( p1, p3 );

  auto l3 = set::make_relation( p4, p5 );
  auto l4 = set::make_relation( p4, p6 );

  auto l5 = set::make_relation( p7, p8 );
  auto l6 = set::make_relation( p7, p9 );

  checkPoints( std::vector< glm::vec3 >{ gp1, gp2 }, l1.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp1, gp3 }, l2.getBasePoints( ) );

  checkPoints( std::vector< glm::vec3 >{ gp4, gp5 }, l3.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp4, gp6 }, l4.getBasePoints( ) );

  checkPoints( std::vector< glm::vec3 >{ gp7, gp8 }, l5.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp7, gp9 }, l6.getBasePoints( ) );


  // planes
  auto t1 = set::make_relation( l1, l2 );

  auto t2 = set::make_relation( l3, l4 );

  auto t3 = set::make_relation( l5, l6 );

  checkPoints( std::vector< glm::vec3 >{ gp1, gp2, gp1, gp3 }, t1.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp4, gp5, gp4, gp6 }, t2.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp7, gp8, gp7, gp9 }, t3.getBasePoints( ) );


  // volume
  auto v1 = set::make_relation( t1, t2 );

  auto v2 = set::make_relation( t2, t3 );

  checkPoints( std::vector< glm::vec3 >{ gp1, gp2, gp1, gp3,
                                         gp4, gp5, gp4, gp6 },  v1.getBasePoints( ) );
  checkPoints( std::vector< glm::vec3 >{ gp4, gp5, gp4, gp6,
                                         gp7, gp8, gp7, gp9 }, v2.getBasePoints( ) );


  // temporal volume
  auto tv1 = set::make_relation( v1, v2 );

  checkPoints( std::vector< glm::vec3 >{ gp1, gp2, gp1, gp3,
                                         gp4, gp5, gp4, gp6,
                                         gp4, gp5, gp4, gp6,
                                         gp7, gp8, gp7, gp9 }, tv1.getBasePoints( ) );
}



/////////////////////////////////////////////////////////////////
/// \brief LevelsAreCorrect
/////////////////////////////////////////////////////////////////
TEST_F( RelationUnitTests, LevelsAreCorrect )
{
  // points
  auto p1 = set::make_relation( 0.0f, 0.0f, 0.0f );
  auto p2 = set::make_relation( 1.0f, 0.0f, 0.0f );
  auto p3 = set::make_relation( 0.0f, 1.0f, 0.0f );

  auto p4 = set::make_relation( 0.0f, 0.0f, 1.0f );
  auto p5 = set::make_relation( 1.0f, 0.0f, 1.0f );
  auto p6 = set::make_relation( 0.0f, 1.0f, 1.0f );

  auto p7 = set::make_relation( 0.0f, 0.0f, 2.0f );
  auto p8 = set::make_relation( 1.0f, 0.0f, 2.0f );
  auto p9 = set::make_relation( 0.0f, 1.0f, 2.0f );

  ASSERT_EQ( 0, p1.getRelationLevel( ) );
  ASSERT_EQ( 0, p2.getRelationLevel( ) );
  ASSERT_EQ( 0, p3.getRelationLevel( ) );

  ASSERT_EQ( 0, p4.getRelationLevel( ) );
  ASSERT_EQ( 0, p5.getRelationLevel( ) );
  ASSERT_EQ( 0, p6.getRelationLevel( ) );

  ASSERT_EQ( 0, p7.getRelationLevel( ) );
  ASSERT_EQ( 0, p8.getRelationLevel( ) );
  ASSERT_EQ( 0, p9.getRelationLevel( ) );


  // lines
  auto l1 = set::make_relation( p1, p2 );
  auto l2 = set::make_relation( p1, p3 );

  auto l3 = set::make_relation( p4, p5 );
  auto l4 = set::make_relation( p4, p6 );

  auto l5 = set::make_relation( p7, p8 );
  auto l6 = set::make_relation( p7, p9 );

  ASSERT_EQ( 1, l1.getRelationLevel( ) );
  ASSERT_EQ( 1, l2.getRelationLevel( ) );

  ASSERT_EQ( 1, l3.getRelationLevel( ) );
  ASSERT_EQ( 1, l4.getRelationLevel( ) );

  ASSERT_EQ( 1, l5.getRelationLevel( ) );
  ASSERT_EQ( 1, l6.getRelationLevel( ) );


  // planes
  auto t1 = set::make_relation( l1, l2 );

  auto t2 = set::make_relation( l3, l4 );

  auto t3 = set::make_relation( l5, l6 );

  ASSERT_EQ( 2, t1.getRelationLevel( ) );
  ASSERT_EQ( 2, t2.getRelationLevel( ) );
  ASSERT_EQ( 2, t3.getRelationLevel( ) );


  // volume
  auto v1 = set::make_relation( t1, t2 );

  auto v2 = set::make_relation( t2, t3 );

  ASSERT_EQ( 3, v1.getRelationLevel( ) );
  ASSERT_EQ( 3, v2.getRelationLevel( ) );


  // temporal volume
  auto tv1 = set::make_relation( v1, v2 );

  ASSERT_EQ( 4, tv1.getRelationLevel( ) );
}



/////////////////////////////////////////////////////////////////
/// \brief LevelsAreCorrect
/////////////////////////////////////////////////////////////////
TEST_F( RelationUnitTests, SubclassCastingWorks )
{
//  std::vector< std::unique_ptr< set::Geometry > > geomVec;

//  // points
//  auto p1 = set::make_relation( 0.0f, 0.0f, 0.0f );
//  auto p2 = set::make_relation( 1.0f, 0.0f, 0.0f );
//  auto p3 = set::make_relation( 0.0f, 1.0f, 0.0f );

//  auto p4 = set::make_relation( 0.0f, 0.0f, 1.0f );
//  auto p5 = set::make_relation( 1.0f, 0.0f, 1.0f );
//  auto p6 = set::make_relation( 0.0f, 1.0f, 1.0f );

//  auto p7 = set::make_relation( 0.0f, 0.0f, 2.0f );
//  auto p8 = set::make_relation( 1.0f, 0.0f, 2.0f );
//  auto p9 = set::make_relation( 0.0f, 1.0f, 2.0f );

//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p1 ) );
//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p2 ) );
//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p3 ) );

//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p4 ) );
//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p5 ) );
//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p6 ) );

//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p7 ) );
//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p8 ) );
//  geomVec.push_back( std::unique_ptr< set::Geometry >( &p9 ) );

//  for ( auto & geom : geomVec )
//  {
//    auto &rel = geom->getSubClass< 0, float >( );

//    ASSERT_EQ(
//              typeid( set::Relation0 ),
//              typeid( rel )
//              );
//  }

}


} // namespace
