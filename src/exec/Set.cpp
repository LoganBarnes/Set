// Set.cpp

#include <iostream>

#include "shared/core/EventDriver.hpp"
#include "shared/core/World.hpp"
#include "SetIOHandler.hpp"
#include "SetConfig.hpp"



/////////////////////////////////////////////
/// \brief main
/// \return
///
/// \author Logan Barnes
/////////////////////////////////////////////
int
main(
     int          argc, ///< number of arguments
     const char **argv  ///< array of argument strings
     )
{
  shared::Driver::printProjectInfo(
                                   set::PROJECT_NAME,
                                   set::VERSION_MAJOR,
                                   set::VERSION_MINOR,
                                   set::VERSION_PATCH
                                   );

  try
  {
    //
    // create world to handle physical updates
    // and ioHandler to interface between the
    // world and the user
    //
    shared::World world;
    set::SetIOHandler io( world );

    //
    // pass world and ioHandler to driver
    // to manage event loop
    //
    shared::EventDriver driver( world, io );

    //
    // run program
    //
    return driver.exec( argc, argv );

  }
  catch ( const std::exception &e )
  {
    std::cerr << "ERROR: program failed: " << e.what( ) << std::endl;
  }

  // should only reach here if an exception is thrown
  return EXIT_FAILURE;

} // main
