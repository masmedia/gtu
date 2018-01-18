#ifndef MONTE_CARLO_SIMULATION_H_20171126_1728
#define MONTE_CARLO_SIMULATION_H_20171126_1728
#include <iostream>
namespace Monte_Carlo_Simulation_NS{
    class Monte_Carlo_Simulation{
        private:
            uint64_t noTests_;
            uint64_t noHunters_;
            uint64_t spacing_;

        public:
            /** Default constructor */
            Monte_Carlo_Simulation();

            /** Three Argument Constructor*/
            Monte_Carlo_Simulation(const uint64_t, const uint64_t, const uint64_t);

            /** Default destructor */
            ~Monte_Carlo_Simulation();

            /** Getters */
            const uint64_t NoTests_() const;
            const uint64_t NoHunters_() const;
            const uint64_t Spacing_() const;

            /** Simulation */
            void simulate();
    };
}
#endif // MONTE_CARLO_SIMULATION_H_20171126_1728
