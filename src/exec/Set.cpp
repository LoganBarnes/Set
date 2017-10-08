#include <iostream>
#include <sim-driver/OpenGLSimulation.hpp>

class Set
{
public:
    Set(int, int) {};

private:
//    std::vector<set::Geometry> geometry_;
};

int main()
{
    try {
        sim::OpenGLSimulation<Set> sim;
        sim.runEventLoop();
    }
    catch (const std::exception &e) {
        std::cerr << "ERROR: program failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
