// AxisRenderer.hpp
#pragma once

// shared
#include "shared/graphics/GraphicsForwardDeclarations.hpp"
#include "glm/glm.hpp"
#include <glad/glad.h>

// system
#include <vector>
#include <memory>



namespace set
{


class AxisRenderer
{

public:

  /////////////////////////////////////////////
  /// \brief AxisRenderer
  /////////////////////////////////////////////
  explicit
  AxisRenderer( );


  /////////////////////////////////////////////
  /// \brief ~AxisRenderer
  /////////////////////////////////////////////
  ~AxisRenderer( );


  /////////////////////////////////////////////
  /// \brief render
  /// \param camera
  /////////////////////////////////////////////
  void render ( const shg::GlmCamera< float > &camera );


  /////////////////////////////////////////////
  /// \brief renderGui
  /////////////////////////////////////////////
  void renderGui ( );


private:

  /////////////////////////////////////////////
  /// \brief _buildVBO
  /// \param pVbo
  /// \param pSettings
  /////////////////////////////////////////////
  void _buildVBO (
                  std::vector< float >           *pVbo,
                  std::vector< shg::VAOElement > *pVaoVec,
                  GLsizei                        *pVaoTotalStride
                  );

  bool showAxes_ = true;
  bool showGrid_ = true;

  int cellRadius_       = 10;
  float singleCellSize_ = 2.0f;

  glm::vec3 gridColor_ = glm::vec3( 0.4f );

  int numGridVerts_ = 0;

  std::unique_ptr< shg::StandardPipeline > upGLIds_;

};



} // namespace set
