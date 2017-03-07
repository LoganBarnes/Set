// Geometry.hpp
#pragma once


#include <vector>
#include "glm/glm.hpp"


namespace set
{

template< typename ... Ts >
class Relation;

class Geometry
{

public:

  explicit
  Geometry( const int relationLevel )
    : relationLevel_( relationLevel )
  { }

  virtual
  ~Geometry( ) { }

  virtual
  std::vector< glm::vec3 > getBasePoints ( ) const = 0;

  int
  getRelationLevel( ) const { return relationLevel_; }


  virtual glm::vec3 &getPoint ( ) = 0;

  virtual Geometry &getA ( ) = 0;
  virtual Geometry &getB ( ) = 0;


private:

  const int relationLevel_;

};


} // namespace set
