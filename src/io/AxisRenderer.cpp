#include "AxisRenderer.hpp"

// project
#include "SetConfig.hpp"

// shared
#include "shared/graphics/OpenGLHelper.hpp"
#include "shared/graphics/OpenGLWrapper.hpp"
#include "shared/graphics/GlmCamera.hpp"
#include "imgui.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

// system
#include <cassert>
#include <iostream>



namespace set
{


namespace
{

void
setVertex(
          std::vector< float > &verts,
          size_t               &index,
          const float          x,
          const float          y,
          const float          z,
          const glm::vec3      &color
          )
{
  verts[ index++ ] = x;
  verts[ index++ ] = y;
  verts[ index++ ] = z;

  verts[ index++ ] = color.r;
  verts[ index++ ] = color.g;
  verts[ index++ ] = color.b;
}



}


///////////////////////////////////////////////////////////////
/// \brief Set::Set
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
AxisRenderer::AxisRenderer( )
  : showAxes_( true )
  , showGrid_( true )
  , cellRadius_( 10 )
  , singleCellSize_( 2.0f )
  , gridColor_( 0.4f )
  , numGridVerts_( 0 )
  , upGLIds_( new graphics::StandardPipeline )
{
  upGLIds_->program =
    graphics::OpenGLHelper::createProgram(
                                          set::SHADER_PATH + "colored/shader.vert",
                                          set::SHADER_PATH + "colored/shader.frag"
                                          );

  std::vector< float > vbo;
  std::vector< graphics::VAOElement > vaoVec;
  GLsizei vaoTotalStride;

  _buildVBO( &vbo, &vaoVec, &vaoTotalStride );

  upGLIds_->vbo = graphics::OpenGLHelper::createBuffer(
                                                       vbo.data( ),
                                                       vbo.size( )
                                                       );

  upGLIds_->vao = graphics::OpenGLHelper::createVao(
                                                    upGLIds_->program,
                                                    upGLIds_->vbo,
                                                    vaoTotalStride,
                                                    vaoVec
                                                    );
}



///////////////////////////////////////////////////////////////
/// \brief AxisRenderer::~AxisRenderer
///
///        Must define deleter in cpp for use with
///        unique_ptr forward declared classes
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
AxisRenderer::~AxisRenderer( )
{}



///////////////////////////////////////////////////////////////
/// \brief Set::render
/// \param alpha
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
void
AxisRenderer::render( const graphics::GlmCamera< float > &camera )
{
  if ( showGrid_ || showAxes_ )
  {
    glUseProgram( *upGLIds_->program );

    glm::mat4 projViewModel = camera.getPerspectiveProjectionViewMatrix( );

    graphics::OpenGLHelper::setMatrixUniform(
                                             upGLIds_->program,
                                             "projectionViewModel",
                                             glm::value_ptr( projViewModel )
                                             );

    if ( showGrid_ )
    {
      graphics::OpenGLHelper::renderBuffer(
                                           upGLIds_->vao,
                                           0,
                                           numGridVerts_ - ( showAxes_ ? 4 : 0 ),
                                           GL_LINES
                                           );
    }

    if ( showAxes_ )
    {
      graphics::OpenGLHelper::renderBuffer( upGLIds_->vao, numGridVerts_, 6, GL_LINES );
    }
  }
} // AxisRenderer::onRender



///////////////////////////////////////////////////////////////
/// \brief AxisRenderer::renderGui
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
void
AxisRenderer::renderGui( )
{
  //
  // Control listing
  //
  if ( ImGui::CollapsingHeader( "Grid", "grid", false, true ) )
  {
    ImGui::Checkbox( "Show Grid  ", &showGrid_ );
    ImGui::SameLine( );
    ImGui::Checkbox( "Show Axes  ", &showAxes_ );
  }
} // AxisRenderer::onGuiRender



///////////////////////////////////////////////////////////////
/// \brief AxisRenderer::_buildVBO
///
/// \author Logan Barnes
///////////////////////////////////////////////////////////////
void
AxisRenderer::_buildVBO(
                        std::vector< float >                *pVbo,           ///<
                        std::vector< graphics::VAOElement > *pVaoVec,        ///<
                        GLsizei                             *pVaoTotalStride ///>
                        )
{
  std::vector< float > &vbo = *pVbo;

  // grid
  size_t size = static_cast< size_t >( cellRadius_ ) * 8 + 4;
  size *= 6;

  // axes
  size += 36;

  vbo.resize( size );

  size_t index = 0;

  float maxDist = cellRadius_ * singleCellSize_;

  // grid
  {
    float distFromAxis;

    for ( int r = -cellRadius_; r <= cellRadius_; ++r )
    {
      if ( r == 0 )
      {
        continue;
      }

      distFromAxis = r * singleCellSize_;

      // line parallel to X-axis
      setVertex( vbo, index, -maxDist,     0.0, distFromAxis, gridColor_ );
      setVertex( vbo, index, maxDist,      0.0, distFromAxis, gridColor_ );

      // line parallel to Z-axis
      setVertex( vbo, index, distFromAxis, 0.0, -maxDist,     gridColor_ );
      setVertex( vbo, index, distFromAxis, 0.0, maxDist,      gridColor_ );
    }

    // X-axis
      setVertex( vbo, index, -maxDist, 0.0, 0.0,      gridColor_ );
      setVertex( vbo, index, maxDist,  0.0, 0.0,      gridColor_ );

    // Z-axis
      setVertex( vbo, index, 0.0,      0.0, -maxDist, gridColor_ );
      setVertex( vbo, index, 0.0,      0.0, maxDist,  gridColor_ );
  }

  numGridVerts_ = index / 6;

  // axes
  {
    // X-axis
    glm::vec3 color ( 1.0f, 0.0f, 0.0f );
      setVertex( vbo, index, -maxDist, 0.0, 0.0, color );
      setVertex( vbo, index, maxDist,  0.0, 0.0, color );

    // Y-axis
    color = glm::vec3( 0.0f, 1.0f, 0.0f );
      setVertex( vbo, index, 0.0,       -maxDist, 0.0, color );
      setVertex( vbo, index, 0.0, maxDist,        0.0, color );

    // Z-axis
    color = glm::vec3( 0.0f, 0.0f, 1.0f );
      setVertex( vbo, index, 0.0, 0.0, -maxDist, color );
      setVertex( vbo, index, 0.0, 0.0, maxDist,  color );
  }

  assert( index == size );

  pVaoVec->clear( );

  float *pointer = 0;
  GLint elmtSize = 3;

  *pVaoTotalStride = static_cast< GLsizei >( sizeof( GLfloat ) ) * 6;

  pVaoVec->push_back( { "inPosition", elmtSize, GL_FLOAT, pointer } );
  pointer += elmtSize;
  pVaoVec->push_back( { "inColor", elmtSize, GL_FLOAT, pointer } );
} // AxisRenderer::_buildVBO



} // namespace set
