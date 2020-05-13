#include <fmi4cpp/fmi4cpp.hpp>

#include <iostream>
#include <string>

using namespace fmi4cpp;

class FMULoader {
public:
    FMULoader() {
        fmi2::fmu fmu("ExternalSim_Test.fmu");
    }


private:

    const double stop = 10;
    const double stepSize = 1E-3;

};