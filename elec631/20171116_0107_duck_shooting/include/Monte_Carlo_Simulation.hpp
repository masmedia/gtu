#ifndef MONTE_CARLO_SIMULATION_H_20171126_1728
#define MONTE_CARLO_SIMULATION_H_20171126_1728

namespace Monte_Carlo_Simulation_NS{
    class Monte_Carlo_Simulation{
        private:
            int noTests_;
            int noHunters_;
            int spacing_;

        public:
            /** Default constructor */
            Monte_Carlo_Simulation();

            /** Three Argument Constructor*/
            Monte_Carlo_Simulation(const int, const int, const int);

            /** Default destructor */
            ~Monte_Carlo_Simulation();

            /** Getters */
            const int NoTests_() const;
            const int NoHunters_() const;
            const int Spacing_() const;

            /** Simulation */
            void simulate();
    };
}
#endif // MONTE_CARLO_SIMULATION_H_20171126_1728
