#include "Monte_Carlo_Simulation.hpp"

int main(){
    using namespace Monte_Carlo_Simulation_NS;

    const int noTests = 10000;
    const int noHunters = 10;
    const int spacing = 31;

    Monte_Carlo_Simulation mcs(noTests, noHunters, spacing);
    mcs.simulate();

    return 0;
}
