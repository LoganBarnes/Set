#include "SetIOHandler.hpp"

// system
#include <vector>
#include <algorithm>

// shared
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "graphics/glfw/GlfwWrapper.hpp"
#include "graphics/opengl/OpenGLWrapper.hpp"
#include "graphics/Camera.hpp"
#include "io/ImguiCallback.hpp"
#include "imgui.h"

// project
#include "SetCallback.hpp"
#include "SetConfig.hpp"


namespace set
{


namespace
{

constexpr int defaultWidth  = 1280;
constexpr int defaultHeight = 720;

}


/////////////////////////////////////////////
/// \brief Set::Set
///
/// \author Logan Barnes
/////////////////////////////////////////////
SetIOHandler::SetIOHandler( shared::World &world )
  : ImguiOpenGLIOHandler( world, true, defaultWidth, defaultHeight, true )
{

  std::unique_ptr< graphics::Callback > upCallback( new SetCallback( *this ) );

  imguiCallback_->setCallback( std::move( upCallback ) );

  //
  // camera
  //
  upCamera_->setAspectRatio( defaultWidth * 1.0f / defaultHeight );
  upCamera_->updateOrbit( 20.0f, 45.0f, -30.0f );

}



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

  this->showWorld( 1.0 );

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

} // SetIOHandler::onRender



/////////////////////////////////////////////
/// \brief SetIOHandler::_onGuiRender
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
SetIOHandler::_onGuiRender( )
{

  bool alwaysTrue = true;

  ImGui::SetNextWindowSize( ImVec2( 345, defaultHeight * 1.0f ), ImGuiSetCond_FirstUseEver );
  ImGui::SetNextWindowPos ( ImVec2( 0, 0 ), ImGuiSetCond_FirstUseEver );

  ImGui::Begin( "Light Bender Settings", &alwaysTrue );

  //
  // FPS
  //
  ImGui::Text(
              "Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO( ).Framerate,
              ImGui::GetIO( ).Framerate
              );

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
