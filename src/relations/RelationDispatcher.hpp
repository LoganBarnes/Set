// RelationDispatcher.hpp
#pragma once


#include <vector>
#include "glm/glm.hpp"
#include "Geometry.hpp"


namespace set
{

template< int Level, typename ... Ts >
class Relation;


class RelationDispatcher
{

public:

  // Declare overloads for each kind of a file to dispatch
//  virtual
//  Relation< float >&
//  dispatch( Relation< float > &relation )
//  {
//    return relation;
//  }

//  virtual
//  Relation< Relation< float > >&
//  dispatch( Relation< Relation< float > > &relation )
//  {
//    return relation;
//  }

//  virtual
//  Relation< Relation< Relation< float > > >&
//  dispatch( Relation< Relation< Relation< float > > > &relation )
//  {
//    return relation;
//  }

//  virtual
//  Relation< Relation< Relation< Relation< float > > > >&
//  dispatch( Relation< Relation< Relation< Relation< float > > > > &relation )
//  {
//    return relation;
//  }

//  template< int Level >
//  Geometry &dispatch ( Geometry &geom );

//  // template< int Level >


};


//template< >
//Relation< 0, float >&
//RelationDispatcher::dispatch< 0 >( Geometry &geom )
//{
//  return static_cast< Relation< 0, float >& >( geom );
//}



} // namespace set
