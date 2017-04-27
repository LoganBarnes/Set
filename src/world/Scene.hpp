// GpuScene.hpp
#pragma once

// shared
#include "shared/graphics/GraphicsForwardDeclarations.hpp"

// system
#include <memory>


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
  std::vector<  > getGeometry ( ) const;


  /////////////////////////////////////////////
  /// \brief renderGui
  /////////////////////////////////////////////
  void renderGui ( );


private:

  shg::OpenGLWrapper &graphics_;

  std::vector< std::unique_ptr< Geometry > > relations_;

//  std::unordered_map< int, std::vector< T > > relations_;

};



} // namespace set
