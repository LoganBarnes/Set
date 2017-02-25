// SetCallback.hpp
#pragma once

#include "io/SharedCallback.hpp"

namespace set
{

class SetIOHandler;


class SetCallback : public shared::SharedCallback
{
public:

  SetCallback( SetIOHandler &handler );

  virtual
  ~SetCallback( );


  virtual
  void handleWindowSize (
                         GLFWwindow *pWindow,
                         int         width,
                         int         height
                         );

  virtual
  void handleMouseButton (
                          GLFWwindow *pWindow,
                          int         button,
                          int         action,
                          int         mods
                          );

  virtual
  void handleKey (
                  GLFWwindow *pWindow,
                  int         key,
                  int         scancode,
                  int         action,
                  int         mods
                  );

  virtual
  void handleCursorPosition (
                             GLFWwindow *pWindow,
                             double      xpos,
                             double      ypos
                             );

  virtual
  void handleScroll (
                     GLFWwindow *pWindow,
                     double      xoffset,
                     double      yoffset
                     );


private:

  SetIOHandler &handler_;

  bool leftMouseDown_;
  bool rightMouseDown_;

  bool shiftDown_;
  bool ctrlDown_;

  double prevX_;
  double prevY_;

};


} //  namespace set

