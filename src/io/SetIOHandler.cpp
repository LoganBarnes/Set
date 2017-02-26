#include "SetIOHandler.hpp"

// system
#include <vector>
#include <algorithm>

// shared
#include "imgui.h"
#include "graphics/opengl/OpenGLWrapper.hpp"
#include "graphics/Camera.hpp"
#include "io/ImguiCallback.hpp"

// project
#include "SetCallback.hpp"
#include "SetConfig.hpp"
#include "Environment.hpp"


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
SetIOHandler::SetIOHandler( shared::World &world )
  : ImguiOpenGLIOHandler( world, true, defaultWidth, defaultHeight )
  , upEnvironment_( new Environment( *upGLWrapper_ ) )
{
  std::unique_ptr< graphics::Callback > upCallback( new SetCallback( *this ) );

  imguiCallback_->setCallback( std::move( upCallback ) );
  imguiCallback_->setEventHandler( this );

  //
  // camera
  //
  upCamera_->setAspectRatio( defaultWidth * 1.0f / defaultHeight );
  upCamera_->updateOrbit( 30.0f, 20.0f, -30.0f );

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
  upCamera_->updateOrbit( 0.f, static_cast< float >( deltaX ), static_cast< float >( deltaY ) );
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
  upCamera_->updateOrbit( static_cast< float >( deltaZ * 0.25 ), 0.f, 0.f );
}



/////////////////////////////////////////////
/// \brief SetIOHandler::resize
/// \param w
/// \param h
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
SetIOHandler::resize(
                     int w,
                     int h
                     )
{
  upGLWrapper_->setViewportSize( w, h );
  upCamera_->setAspectRatio( w * 1.0f / h );
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

  upEnvironment_->render( *upCamera_ );

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

  ImGui::SetNextWindowSize( ImVec2( 345, defaultHeight * 1.0f ), ImGuiSetCond_FirstUseEver );
//  ImGui::SetNextWindowSize( ImVec2( 0, 0 ) ); // auto scale size?
  ImGui::SetNextWindowPos ( ImVec2( 0, 0 ), ImGuiSetCond_FirstUseEver );

  ImGui::Begin( "Settings", &alwaysOpen );

  upEnvironment_->renderGui( );

  //
  // Control listing
  //
  if ( ImGui::CollapsingHeader( "Controls", "controls", false, true ) )
  {

    ImGui::Text(
                "Camera Movement:\n\n"
                "    Left Mouse      -    Rotate\n" \
                "    Right Mouse     -    Zoom\n"   \
                "    Middle Scroll   -    Zoom\n"
                );

  }

  ImGui::End( );

} // SetIOHandler::onGuiRender



} // namespace set
