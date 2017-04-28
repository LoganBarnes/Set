// Geometry.hpp
#pragma once

#ifdef __CUDACC__
#include <cuda_runtime.h>
#define CUDA_CALLABLE_MEMBER __host__ __device__
#else
#define CUDA_CALLABLE_MEMBER
#endif

#include <glm/glm.hpp>
#include <vector>


namespace set
{

template< int Level, typename ... Ts >
class Relation;

class Geometry
{

public:

  CUDA_CALLABLE_MEMBER
  explicit
  Geometry( const int relationLevel )
    : relationLevel_( relationLevel )
  { }


  CUDA_CALLABLE_MEMBER
  virtual
  ~Geometry( ) { }


  CUDA_CALLABLE_MEMBER
  Geometry( const Geometry &other )
    : relationLevel_( other.relationLevel_ )
  {}


  virtual
  std::vector< glm::vec3 > getBasePoints ( ) const = 0;


  const int&
  getRelationLevel( ) const { return relationLevel_; }


  virtual glm::vec3 &getPoint ( ) = 0;

  virtual Geometry &getA ( ) = 0;
  virtual Geometry &getB ( ) = 0;


private:

  const int relationLevel_;

};

} // namespace set
