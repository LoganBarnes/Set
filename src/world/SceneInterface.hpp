// SceneInterface.hpp
#pragma once

// system
#include <memory>

// shared
#include "shared/graphics/GraphicsForwardDeclarations.hpp"


namespace set
{

class Geometry;


class SceneInterface
{

public:

  /////////////////////////////////////////////
  /// \brief SceneInterface
  /////////////////////////////////////////////
  explicit
  SceneInterface( shg::OpenGLWrapper &graphics );


  virtual
  ~SceneInterface( ) = default;


  /////////////////////////////////////////////
  /// \brief render
  /// \param alpha
  /////////////////////////////////////////////
  void render ( const shg::Camera< float > &camera ) = 0;


  /////////////////////////////////////////////
  /// \brief renderGui
  /////////////////////////////////////////////
  void renderGui ( ) = 0;


protected:


};



} // namespace set
