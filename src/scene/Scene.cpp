#include "Scene.hpp"

// system
#include <cassert>
#include <iostream>

// shared
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "shared/graphics/OpenGLWrapper.hpp"
#include "shared/graphics/Camera.hpp"

// project
#include "SetConfig.hpp"
#include "Relation.hpp"

#ifdef USE_CUDA
#include "CudaWrappers.cuh"
#include "CudaScene.cuh"
#define cuda_func( func ) func
#else // USE_CUDA
#define cuda_func( x ) static_cast< void >( 0 )
#endif // USE_CUDA

namespace set
{


/////////////////////////////////////////////
/// \brief Set::Set
///
/// \author Logan Barnes
/////////////////////////////////////////////
Scene::Scene( graphics::OpenGLWrapper &graphics )
  : graphics_( graphics )
{
  cuda_func( cuda_initScene( ) );

  cuda_func( cuda_addRelation( 1, 2, 3 ) );
  cuda_func( cuda_addRelation( 2, 3, 4 ) );
  cuda_func( cuda_addRelation( 3, 4, 5 ) );
  cuda_func( cuda_addRelation( 4, 5, 6 ) );
  cuda_func( cuda_addRelation( 5, 6, 7 ) );
  cuda_func( cuda_addRelation( 6, 7, 8 ) );
}



Scene::~Scene( )
{
  cuda_func( cuda_clearScene( ) );
}



/////////////////////////////////////////////
/// \brief Set::render
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
Scene::render( const graphics::Camera< float > &/*camera*/ )
{} // Scene::onRender



/////////////////////////////////////////////
/// \brief Scene::renderGui
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
Scene::renderGui( )
{
  //
  // Scene manipulation
  //
  if ( ImGui::CollapsingHeader( "Scene", "scene", false, true ) )
  {
    ImGui::Text( "Scene info goes here..." );
  }
} // Scene::onGuiRender



} // namespace set
