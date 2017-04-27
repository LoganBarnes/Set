#include "SetIOHandler.hpp"

// system
#include <vector>
#include <algorithm>

// shared
#include "imgui.h"
#include "shared/graphics/OpenGLWrapper.hpp"
#include "shared/graphics/GlmCamera.hpp"
#include "shared/graphics/ImguiCallback.hpp"

// project
#include "SetCallback.hpp"
#include "SetConfig.hpp"
#include "SetWorld.hpp"
#include "AxisRenderer.hpp"


namespace set
{


namespace
{

constexpr int defaultWidth  = 1280;
constexpr int defaultHeight = 720;

glm::vec3 backgroundColor = glm::vec3( 0.6f );

}


/////////////////////////////////////////////
/// \brief Set::Set
///
/// \author Logan Barnes
/////////////////////////////////////////////
SetIOHandler::SetIOHandler( SetWorld &world )
  : ImguiOpenGLIOHandler( world, true, defaultWidth, defaultHeight )
  , setWorld_( world )
  , upAxisRenderer_( new AxisRenderer )
{
  std::unique_ptr< graphics::Callback > upCallback( new SetCallback( *this ) );

  imguiCallback_->setCallback( std::move( upCallback ) );

  //
  // camera
  //
  upCamera_->setAspectRatio( defaultWidth * 1.0f / defaultHeight );
//  upCamera_->updateOrbit( 30.0f, 20.0f, -30.0f );

  upGLWrapper_->setClearColor(
                              backgroundColor.r,
                              backgroundColor.g,
                              backgroundColor.b,
                              1.0
                              );
}



SetIOHandler::~SetIOHandler( )
{}



/////////////////////////////////////////////
/// \brief SetIOHandler::rotateCamera
/// \param deltaX
/// \param deltaY
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
SetIOHandler::rotateCamera(
                           double deltaX,
                           double deltaY
                           )
{
//  upCamera_->updateOrbit( 0.f, static_cast< float >( deltaX ), static_cast< float >( deltaY ) );
}



/////////////////////////////////////////////
/// \brief SetIOHandler::zoomCamera
/// \param deltaZ
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
SetIOHandler::zoomCamera( double deltaZ )
{
//  upCamera_->updateOrbit( static_cast< float >( deltaZ * 0.25 ), 0.f, 0.f );
}



/////////////////////////////////////////////
/// \brief Set::onRender
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
SetIOHandler::_onRender( const double )
{

  upGLWrapper_->clearWindow( );

  upAxisRenderer_->render( *upCamera_ );

} // SetIOHandler::onRender



/////////////////////////////////////////////
/// \brief SetIOHandler::_onGuiRender
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
SetIOHandler::_onGuiRender( )
{
  bool alwaysOpen = true;

  ImGui::SetNextWindowPos ( ImVec2( 0, 0 ) );

  ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
  ImGui::Begin( "Settings", &alwaysOpen, ImGuiWindowFlags_AlwaysAutoResize );

  upAxisRenderer_->renderGui( );

  //
  // Control listing
  //
  if ( ImGui::CollapsingHeader( "Controls", "controls", false, true ) )
  {
    ImGui::Text(
                "Esc - Quit Program\n\n"            \
                "Camera Movement:\n\n"              \
                "    Left Mouse      -    Rotate\n" \
                "    Right Mouse     -    Zoom\n"   \
                "    Middle Scroll   -    Zoom\n"   \
                "                                   " // space buffer
                );
  }

  ImGui::End( );

} // SetIOHandler::onGuiRender



} // namespace set
