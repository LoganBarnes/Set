// Scene.hpp
#pragma once

// system
#include <vector>
#include <memory>

// shared
#include "glm/glm.hpp"


namespace graphics
{

class OpenGLWrapper;

template< typename T >
class Camera;

struct VAOSettings;

}



namespace set
{

class Geometry;


class Scene
{

public:

  /////////////////////////////////////////////
  /// \brief Scene
  /////////////////////////////////////////////
  Scene( graphics::OpenGLWrapper &graphics );


  ~Scene( );


  /////////////////////////////////////////////
  /// \brief render
  /// \param alpha
  /////////////////////////////////////////////
  void render ( const graphics::Camera< float > &camera );


  /////////////////////////////////////////////
  /// \brief renderGui
  /////////////////////////////////////////////
  void renderGui ( );


private:

  graphics::OpenGLWrapper &graphics_;

  std::vector< std::unique_ptr< Geometry > > relations_;

};



} // namespace set
