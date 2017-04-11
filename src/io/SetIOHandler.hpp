#pragma once


#include <string>
#include "shared/core/ImguiOpenGLIOHandler.hpp"
#include "shared/graphics/GraphicsForwardDeclarations.hpp"



namespace set
{

class SetWorld;
class AxisRenderer;
//class SceneRenderer;


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
  SetIOHandler( SetWorld &world );


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

  set::SetWorld &setWorld_;
  std::unique_ptr< AxisRenderer > upAxisRenderer_;



};


} // namespace set
