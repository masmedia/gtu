#ifndef POISSON_H_20171031_1313
#define POISSON_H_20171031_1313
#include <iostream>
#include <random>

namespace Poisson_NS{
class Poisson{
    private:
        int pVal_;                 //Poisson random variable to be returned
        double mean_;              //Mean value that will be provided for Poisson distribution
        std::mt19937 mt_;          //Uniformly distributed PRNG Mersenne Twister algorithm
        //std::default_random_engine dre_;  //Default random number generator

        std::poisson_distribution<int> pd_;

    public:
        /** Default constructor */
        Poisson();
        Poisson(const int);
        Poisson(const double);

        /** Default destructor */
        ~Poisson();

        /** Copy constructor
         *  \param other Object to copy from
         */
        Poisson(const Poisson& other);

        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Poisson& operator=(const Poisson& other);

        /** Getter for Poisson distribution */
        const int PVal();
        std::poisson_distribution<int>& PD_();
        int generatePVal();

        /** Return a vector of Poisson random variables with given mean*/
        void visualizeDistribution(const double);

    };  //end of Poisson class
    std::ostream& operator<<(std::ostream&, const Poisson&);
}   //end of Poisson_NS
#endif // POISSON_H_20171031_1313
