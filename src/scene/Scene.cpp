#include "Scene.hpp"

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
Scene::Scene( graphics::OpenGLWrapper &graphics )
  : graphics_( graphics )
{}



Scene::~Scene( )
{}



/////////////////////////////////////////////
/// \brief Set::render
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
Scene::render( const graphics::Camera< float > &camera )
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
