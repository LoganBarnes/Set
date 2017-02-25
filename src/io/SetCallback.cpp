#include "SetCallback.hpp"
#include "GLFW/glfw3.h"
#include "SetIOHandler.hpp"


namespace set
{


SetCallback::SetCallback( SetIOHandler &handler )
  : shared::SharedCallback( )
  , handler_       ( handler )
  , leftMouseDown_ ( false )
  , rightMouseDown_( false )
  , shiftDown_     ( false )
  , ctrlDown_      ( false )
{}


SetCallback::~SetCallback( )
{}



///
/// \brief SetCallback::handleWindowSize
/// \param pWindow
/// \param width
/// \param height
///
void
SetCallback::handleWindowSize(
                                      GLFWwindow*,
                                      int width,
                                      int height
                                      )
{

  handler_.resize( width, height );

}



void
SetCallback::handleMouseButton(
                                       GLFWwindow *pWindow,
                                       int         button,
                                       int         action,
                                       int
                                       )
{

  if ( button == GLFW_MOUSE_BUTTON_1 )
  {

    if ( action == GLFW_PRESS )
    {

      leftMouseDown_ = true;
      glfwGetCursorPos( pWindow, &prevX_, &prevY_ );

    }
    else
    {

      leftMouseDown_ = false;

    }
  }
  else
  if ( button == GLFW_MOUSE_BUTTON_2 )
  {

    if ( action == GLFW_PRESS )
    {

      rightMouseDown_ = true;
      glfwGetCursorPos( pWindow, &prevX_, &prevY_ );

    }
    else
    {

      rightMouseDown_ = false;

    }

  }

} // handleMouseButton



void
SetCallback::handleKey(
                               GLFWwindow *pWindow,
                               int         key,
                               int,
                               int         action,
                               int
                               )
{

  switch ( key )
  {

  case GLFW_KEY_ESCAPE:

    if ( action == GLFW_RELEASE )
    {

      glfwSetWindowShouldClose( pWindow, GL_TRUE );

    }

    break;


  case GLFW_KEY_LEFT_SHIFT:
  case GLFW_KEY_RIGHT_SHIFT:

    if ( action == GLFW_PRESS )
    {

      shiftDown_ = true;

    }
    else
    {

      shiftDown_ = false;

    }

    break;


  case GLFW_KEY_LEFT_CONTROL:
  case GLFW_KEY_RIGHT_CONTROL:

    if ( action == GLFW_PRESS )
    {

      ctrlDown_ = true;

    }
    else
    {

      ctrlDown_ = false;

    }

    break;


  case GLFW_KEY_S:

    if ( action == GLFW_RELEASE && ctrlDown_ )
    {
        // save
    }


  case GLFW_KEY_R:

    if ( action == GLFW_RELEASE )
    {
      handler_.showWorld( 1.0 );
    }

  default:

    break;

  } // switch

} // handleKey



//void SetCallback::handleCursorPosition(GLFWwindow *window, double xpos, double ypos)
void
SetCallback::handleCursorPosition(
                                          GLFWwindow*,
                                          double xpos,
                                          double ypos
                                          )
{

  if ( leftMouseDown_ )
  {

    handler_.rotateCamera( prevX_ - xpos, prevY_ - ypos );

  }
  else
  if ( rightMouseDown_ )
  {

    handler_.zoomCamera( prevY_ - ypos );

  }

  prevX_ = xpos;
  prevY_ = ypos;

} // handleCursorPosition



//void SetCallback::handleScroll(GLFWwindow* widnow, double xoffset, double yoffset)
void
SetCallback::handleScroll(
                                  GLFWwindow*,
                                  double,
                                  double yoffset
                                  )
{

  handler_.zoomCamera( yoffset );

}



} //  namespace light
