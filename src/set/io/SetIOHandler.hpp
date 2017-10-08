#pragma once


#include <string>
#include "shared/core/ImguiOpenGLIOHandler.hpp"


namespace graphics
{

class OpenGLWrapper;

template< typename T >
class Camera;

}


namespace shared
{

class World;

}


namespace set
{

class Environment;
class Scene;


/////////////////////////////////////////////
/// \brief The SetIOHandler class
///
/// \author Logan Barnes
/////////////////////////////////////////////
class SetIOHandler : public shared::ImguiOpenGLIOHandler
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief SetIOHandler
  ///////////////////////////////////////////////////////////////
  SetIOHandler( shared::World &world );


  ///////////////////////////////////////////////////////////////
  /// \brief ~SetIOHandler
  ///////////////////////////////////////////////////////////////
  ~SetIOHandler( );


  ///////////////////////////////////////////////////////////////
  /// \brief rotateCamera
  /// \param deltaX
  /// \param deltaY
  ///////////////////////////////////////////////////////////////
  void rotateCamera (
                     double deltaX,
                     double deltaY
                     );


  ///////////////////////////////////////////////////////////////
  /// \brief zoomCamera
  /// \param deltaZ
  ///////////////////////////////////////////////////////////////
  void zoomCamera ( double deltaZ );


protected:

private:

  virtual
  void _onRender ( const double alpha ) final;

  virtual
  void _onGuiRender ( ) final;


  std::unique_ptr< Environment > upEnvironment_;
  std::unique_ptr< Scene > upScene_;


};


} // namespace set
