#include "Environment.hpp"

// system
#include <cassert>
#include <iostream>

// shared
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "imgui.h"
#include "graphics/opengl/OpenGLWrapper.hpp"
#include "graphics/Camera.hpp"

// project
#include "SetConfig.hpp"



namespace set
{


namespace
{

bool showAxes = true;
bool showGrid = true;

int cellRadius       = 10;
float singleCellSize = 2.0f;

glm::vec3 gridColor = glm::vec3( 0.4f );


int numVerts = 0;


void
setVertex(
          std::vector< float > &verts,
          size_t               &index,
          const float           x,
          const float           y,
          const float           z,
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


/////////////////////////////////////////////
/// \brief Set::Set
///
/// \author Logan Barnes
/////////////////////////////////////////////
Environment::Environment( graphics::OpenGLWrapper &graphics )
  : graphics_( graphics )
{

  graphics_.addProgram(
                       "envProgram",
                       set::SHADER_PATH + "default/shader.vert",
                       set::SHADER_PATH + "default/shader.frag"
                       );

  std::vector< float > vbo;

  _buildVBO( &vbo );

  graphics.addBufferNoVAO(
                          "envBuffer",
                          static_cast< GLsizeiptr >( vbo.size( ) * sizeof( float ) ),
                          vbo.data( ),
                          GL_STATIC_DRAW
                          );

  float *pointer = 0;
  GLint size     = 3;
  GLsizei stride = static_cast< GLsizei >( sizeof( GLfloat ) ) * 6;

  VAOSettings settings;
  settings.names.push_back( "inPosition" );
  settings.sizes.push_back( size );
  settings.types.push_back( GL_FLOAT );
  settings.strides.push_back( stride );
  settings.pointers.push_back( pointer );

  pointer += 3;

  settings.names.push_back( "inColor" );
  settings.sizes.push_back( size );
  settings.types.push_back( GL_FLOAT );
  settings.strides.push_back( stride );
  settings.pointers.push_back( pointer );

  graphics.addVAOToBuffer(
                          "envBuffer",
                          "envProgram",
                          settings
                          );

}



/////////////////////////////////////////////
/// \brief Set::render
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
Environment::render( const graphics::Camera< float > &camera )
{

  if ( showGrid || showAxes )
  {
    graphics_.useProgram( "envProgram" );

    glm::mat4 projViewModel = camera.getProjectionMatrix( ) * camera.getViewMatrix( );

    graphics_.setMatrixUniform(
                               "envProgram",
                               "projectionViewModel",
                               glm::value_ptr( projViewModel )
                               );

    graphics_.renderBuffer( "envBuffer", 0, numVerts - ( showAxes ? 0 : 6 ), GL_LINES );
  }

} // Environment::onRender



/////////////////////////////////////////////
/// \brief Environment::renderGui
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
Environment::renderGui( )
{

  //
  // Control listing
  //
  if ( ImGui::CollapsingHeader( "Grid", "grid", false, true ) )
  {
    ImGui::Checkbox( "Show Grid", &showGrid );

    ImGui::Checkbox( "Show Axes", &showAxes );
  }

} // Environment::onGuiRender



void
Environment::_buildVBO( std::vector< float > *pVbo )
{

  std::vector< float > &vbo = *pVbo;

  size_t size = 0;

  if ( showGrid )
  {
    size  = static_cast< size_t >( cellRadius ) * 8 + ( showAxes ? 0 : 4 );
    size *= 6;
  }

  if ( showAxes )
  {
    size += 36;
  }

  vbo.resize( size );

  size_t index = 0;

  float maxDist = cellRadius * singleCellSize;

  if ( showGrid )
  {
    float distFromAxis;

    for ( int r = -cellRadius; r <= cellRadius; ++r )
    {
      if ( showAxes && r == 0 )
      {
        continue;
      }

      distFromAxis = r * singleCellSize;

      // line parallel to X axis
      setVertex( vbo, index, -maxDist,     0.0, distFromAxis, gridColor );
      setVertex( vbo, index, maxDist,      0.0, distFromAxis, gridColor );

      // line parallel to Z axis
      setVertex( vbo, index, distFromAxis, 0.0, -maxDist,     gridColor );
      setVertex( vbo, index, distFromAxis, 0.0, maxDist,      gridColor );
    }

  }

  if ( showAxes )
  {
    // X-axis
    glm::vec3 color ( 1.0f, 0.0f, 0.0f );
    setVertex( vbo, index, -maxDist, 0.0, 0.0, color );
    setVertex( vbo, index, maxDist,  0.0, 0.0, color );

    // Y-axis
    color = glm::vec3( 0.0f, 1.0f, 0.0f );
    setVertex( vbo, index, 0.0, -maxDist, 0.0, color );
    setVertex( vbo, index, 0.0, maxDist,  0.0, color );

    // Z-axis
    color = glm::vec3( 0.0f, 0.0f, 1.0f );
    setVertex( vbo, index, 0.0, 0.0, -maxDist, color );
    setVertex( vbo, index, 0.0, 0.0, maxDist,  color );
  }

  numVerts = size / 6;

//  int counter = 0;
//  bool isColor = false;
//  std::cout << "V: ";
//  for ( float &f : vbo )
//  {
//    std::cout << f << " ";
//    if ( ++counter % 3 == 0 )
//    {
//      isColor = !isColor;
//      std::cout << std::endl;
//      if ( isColor )
//        std::cout << "C: ";
//      else
//        std::cout << "V: ";
//      std::cout << counter / 6;
//    }
//  }

  assert( index == size );
  assert( 0 );

} // Environment::_buildVBO



} // namespace set
