// Environment.hpp
#pragma once

// system
#include <vector>

// shared
#include "glm/glm.hpp"
#include "shared/graphics/GraphicsForwardDeclarations.hpp"



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

  void _buildVBO (
                  std::vector< float >  *pVbo,
                  graphics::VAOSettings *pSettings
                  );

  graphics::OpenGLWrapper &graphics_;

  bool showAxes_ = true;
  bool showGrid_ = true;

  int cellRadius_       = 10;
  float singleCellSize_ = 2.0f;

  glm::vec3 gridColor_ = glm::vec3( 0.4f );

  int numGridVerts_ = 0;

};



} // namespace set
