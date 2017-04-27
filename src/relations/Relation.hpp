// Relation.hpp
#pragma once

#include "Geometry.hpp"
#include <glm/glm.hpp>

#include <vector>
#include <stdexcept>


namespace set
{


typedef Relation< 0, float >     Relation0;
typedef Relation< 1, Relation0 > Relation1;
typedef Relation< 2, Relation1 > Relation2;
typedef Relation< 3, Relation2 > Relation3;
typedef Relation< 4, Relation3 > Relation4;


template< int Level, typename ... Ts >
class Relation;


/////////////////////////////////////////////////////////////////
/// \brief The Relation<T> class
///
///        Base class for templated Relation classes. Contains
///        a single vec3 point
///
/////////////////////////////////////////////////////////////////
template< typename T >
class Relation< 0, T >: public Geometry
{

public:

  /////////////////////////////////////////////////////////////////
  /// \brief Relation
  /// \param x_
  /// \param y_
  /// \param z_
  /////////////////////////////////////////////////////////////////
  CUDA_CALLABLE_MEMBER
  Relation(
           T x_ = 0,
           T y_ = 0,
           T z_ = 0
           )
    : Geometry( 0 )
    , point_( x_, y_, z_ )
  {}


  CUDA_CALLABLE_MEMBER
  ~Relation( ) = default;


  CUDA_CALLABLE_MEMBER
  Relation( const Relation &other ) : Geometry( other )
  {
    point_ = other.point_;
  }


  CUDA_CALLABLE_MEMBER
  Relation&
  operator=( const Relation &other )
  {
    Relation r( other );
    *this = r;
    return *this;
  }


  /////////////////////////////////////////////////////////////////
  /// \brief getBasePoints
  /// \return
  /////////////////////////////////////////////////////////////////
  std::vector< glm::vec3 >
  getBasePoints( ) const
  {
    std::vector< glm::vec3 > points {
      point_
    };
    return points;
  }


  /////////////////////////////////////////////////////////////////
  /// \brief getPoint
  /// \return
  /////////////////////////////////////////////////////////////////
  virtual
  glm::vec3&
  getPoint( ) { return point_; }


  /////////////////////////////////////////////////////////////////
  /// \brief getA
  /// \return
  /////////////////////////////////////////////////////////////////
  virtual
  Geometry&
  getA( ) { throw std::runtime_error( "Cannot retrieve sub relation of 0-level relation" ); }


  /////////////////////////////////////////////////////////////////
  /// \brief getB
  /// \return
  /////////////////////////////////////////////////////////////////
  virtual
  Geometry&
  getB( ) { throw std::runtime_error( "Cannot retrieve sub relation of 0-level relation" ); }


private:

  glm::vec3 point_;
};



/////////////////////////////////////////////////////////////////
/// \brief The Relation< Relation< Ts > > class
///
///        Templated Relation class representing all high
///        order relations. Contains two lower level child
///        relations (A and B).
///
/////////////////////////////////////////////////////////////////
template< int Level, typename ... Types >
class Relation< Level, Relation< Level - 1, Types ... > >: public Geometry
{

public:

  /////////////////////////////////////////////////////////////////
  /// \brief Relation
  /// \param a
  /// \param b
  /////////////////////////////////////////////////////////////////
  CUDA_CALLABLE_MEMBER
  Relation(
           Relation< Level - 1, Types ... > &a,
           Relation< Level - 1, Types ... > &b
           )
    : Geometry( Level )
    , a_( a )
    , b_( b )
  {}


  CUDA_CALLABLE_MEMBER
  ~Relation( ) = default;


  /////////////////////////////////////////////////////////////////
  /// \brief getBasePoints
  /// \return
  /////////////////////////////////////////////////////////////////
  std::vector< glm::vec3 >
  getBasePoints( ) const
  {
    std::vector< glm::vec3 > points  = a_.getBasePoints( );
    std::vector< glm::vec3 > points2 = b_.getBasePoints( );

    points.insert( std::end( points ), std::begin( points2 ), std::end( points2 ) );

    return points;
  }


  virtual
  glm::vec3&
  getPoint( ) { throw std::runtime_error( "Cannot retrieve point of relation above level 0" ); }

  /////////////////////////////////////////////////////////////////
  /// \brief getA
  /// \return
  /////////////////////////////////////////////////////////////////
  virtual
  Relation< Level - 1, Types ... >&
  getA( ) { return a_; }


  /////////////////////////////////////////////////////////////////
  /// \brief getB
  /// \return
  /////////////////////////////////////////////////////////////////
  virtual
  Relation< Level - 1, Types ... >&
  getB( ) { return b_; }


private:

  Relation< Level - 1, Types ... > &a_;
  Relation< Level - 1, Types ... > &b_;
};



///
/// \brief make_relation
/// \param x
/// \param y
/// \param z
/// \return
///
static
Relation< 0, float >
make_relation(
              float x,
              float y,
              float z
              )
{
  return Relation< 0, float >( x, y, z );
}



///
/// \brief make_relation
/// \param a
/// \param b
/// \return
///
template< int LowerLevel, typename T >
Relation< LowerLevel + 1, Relation< LowerLevel, T > >
make_relation(
              Relation< LowerLevel, T > &a,
              Relation< LowerLevel, T > &b
              )
{
  return Relation< LowerLevel + 1, Relation< LowerLevel, T > >( a, b );
}



} // namespace set
