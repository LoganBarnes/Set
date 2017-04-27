// GpuScene.hpp
#pragma once

// system
#include <memory>

// shared
#include "shared/graphics/GraphicsForwardDeclarations.hpp"


namespace set
{

class Geometry;


class GpuScene
{

public:

  /////////////////////////////////////////////
  /// \brief GpuScene
  /////////////////////////////////////////////
  explicit
  GpuScene( );


  ~GpuScene( );


  /////////////////////////////////////////////
  /// \brief render
  /// \param alpha
  /////////////////////////////////////////////
  std::vector<  > getGeometry() const;


  /////////////////////////////////////////////
  /// \brief renderGui
  /////////////////////////////////////////////
  void renderGui ( );


private:

  graphics::OpenGLWrapper &graphics_;

  std::vector< std::unique_ptr< Geometry > > relations_;

//  std::unordered_map< int, std::vector< T > > relations_;

};



} // namespace set
