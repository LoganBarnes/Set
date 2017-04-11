// CudaScene.cuh
#pragma once


extern "C"
{


namespace set
{

void cuda_initScene( );

void cuda_addRelation( float x, float y, float z );

void cuda_clearScene( );

} // namespace set


} // extern "C"

