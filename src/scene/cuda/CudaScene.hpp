// CudaScene.hpp
#pragma once

// system
#include "Scene.hpp"


namespace set
{


class CudaScene : public Scene
{

public:

  /////////////////////////////////////////////
  /// \brief CudaScene
  /////////////////////////////////////////////
  CudaScene( graphics::OpenGLWrapper &graphics );


  ~CudaScene( );


  /////////////////////////////////////////////
  /// \brief render
  /// \param alpha
  /////////////////////////////////////////////
  virtual
  void render ( const graphics::Camera< float > &camera );


  /////////////////////////////////////////////
  /// \brief renderGui
  /////////////////////////////////////////////
  virtual
  void renderGui ( );


protected:

  graphics::OpenGLWrapper &graphics_;
  std::vector< std::unique_ptr< Geometry > > relations_;


};



} // namespace set
