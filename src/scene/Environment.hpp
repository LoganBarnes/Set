// Environment.hpp
#pragma once

// system
#include <vector>


namespace graphics
{

class OpenGLWrapper;

template< typename T >
class Camera;

}



namespace set
{


class Environment
{

public:

  /////////////////////////////////////////////
  /// \brief Environment
  /////////////////////////////////////////////
  Environment( graphics::OpenGLWrapper &graphics );


  ~Environment( ) = default;


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

  void _buildVBO ( std::vector< float > *pVbo );

  graphics::OpenGLWrapper &graphics_;

};



} // namespace set
