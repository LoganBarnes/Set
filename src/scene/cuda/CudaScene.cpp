#include "CudaScene.hpp"

// system
#include <cassert>
#include <iostream>

// shared
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "graphics/opengl/OpenGLWrapper.hpp"
#include "graphics/Camera.hpp"

// project
#include "SetConfig.hpp"
#include "Relation.hpp"



namespace set
{

/////////////////////////////////////////////
/// \brief Set::Set
///
/// \author Logan Barnes
/////////////////////////////////////////////
CudaScene::CudaScene( graphics::OpenGLWrapper &graphics )
  : graphics_( graphics )
{}



CudaScene::~CudaScene( )
{}



/////////////////////////////////////////////
/// \brief Set::render
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
CudaScene::render( const graphics::Camera< float > &camera )
{} // CudaScene::onRender



/////////////////////////////////////////////
/// \brief CudaScene::renderGui
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
CudaScene::renderGui( )
{
  //
  // CudaScene manipulation
  //
  if ( ImGui::CollapsingHeader( "CudaScene", "Cudascene", false, true ) )
  {
    ImGui::Text( "CudaScene info goes here..." );
  }
} // CudaScene::onGuiRender



} // namespace set
