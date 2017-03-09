#include "CudaScene.cuh"

#include <cuda_runtime.h>
#include <thrust/device_vector.h>

// project
#include "Relation.hpp"


extern "C"
{


  namespace set
  {

  namespace
  {

  thrust::device_vector< Relation0 > *pGeomVec;

  }



  ///
  /// \brief cuda_initScene
  ///
  void
  cuda_initScene( )
  {
    pGeomVec = new thrust::device_vector< Relation0 >( );
  }



  ///
  /// \brief cuda_addRelation
  /// \param x
  /// \param y
  /// \param z
  ///
  void
  cuda_addRelation(
                   float x,
                   float y,
                   float z
                   )
  {
    pGeomVec->push_back( Relation0 ( x, y, z ) );
  }



  ///
  /// \brief cuda_clearScene
  ///
  void
  cuda_clearScene( )
  {
    pGeomVec->clear( );
    pGeomVec->shrink_to_fit( );
    delete pGeomVec;
  }



  } // namespace set


} // extern "C"
