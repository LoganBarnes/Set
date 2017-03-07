// Relation.hpp
#pragma once


#include <vector>
#include <stdexcept>

#include "glm/glm.hpp"
#include "Geometry.hpp"


namespace set
{


template< typename ... Ts >
class Relation;


/////////////////////////////////////////////////////////////////
/// \brief The Relation<T> class
///
///        Base class for templated Relation classes. Contains
///        a single vec3 point
///
/////////////////////////////////////////////////////////////////
template< typename T >
class Relation< T >: public Geometry
{

public:

  /////////////////////////////////////////////////////////////////
  /// \brief Relation
  /// \param x_
  /// \param y_
  /// \param z_
  /////////////////////////////////////////////////////////////////
  Relation(
           T x_,
           T y_,
           T z_
           )
    : Geometry( 0 )
    , point_( x_, y_, z_ )
  {}


  ~Relation( ) = default;


  /////////////////////////////////////////////////////////////////
  /// \brief getBasePoints
  /// \return
  /////////////////////////////////////////////////////////////////
  std::vector< glm::vec3 >
  getBasePoints( ) const
  {
    std::vector< glm::vec3 > points
    {
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
template< typename ... Ts >
class Relation< Relation< Ts ... > >: public Geometry
{

public:

  /////////////////////////////////////////////////////////////////
  /// \brief Relation
  /// \param a
  /// \param b
  /////////////////////////////////////////////////////////////////
  Relation(
           Relation< Ts ... > &a,
           Relation< Ts ... > &b
           )
    : Geometry( a.getRelationLevel( ) + 1 )
    , a_( a )
    , b_( b )
  {}


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
  Relation< Ts ... >&
  getA( ) { return a_; }


  /////////////////////////////////////////////////////////////////
  /// \brief getB
  /// \return
  /////////////////////////////////////////////////////////////////
  virtual
  Relation< Ts ... >&
  getB( ) { return b_; }


private:

  Relation< Ts ... > &a_;
  Relation< Ts ... > &b_;
};



///
/// \brief make_relation
/// \param x
/// \param y
/// \param z
/// \return
///
Relation< float >
make_relation(
              float x,
              float y,
              float z
              )
{
  return Relation< float >( x, y, z );
}



///
/// \brief make_relation
/// \param a
/// \param b
/// \return
///
template< typename T >
Relation< Relation< T > >
make_relation(
              Relation< T > &a,
              Relation< T > &b
              )
{
  return Relation< Relation< T > >( a, b );
}



} // namespace set
