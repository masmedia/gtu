#include <random>
#include <ctime>
#include <map>
#include <omp.h>
#include "Monte_Carlo_Simulation.hpp"
#include "Linear_Spacing.hpp"
#include "Matrix.hpp"

//Default Constructor
Monte_Carlo_Simulation_NS::Monte_Carlo_Simulation::Monte_Carlo_Simulation(): noTests_(10000), noHunters_(10), spacing_(31){}
//Constructor
Monte_Carlo_Simulation_NS::
    Monte_Carlo_Simulation::
        Monte_Carlo_Simulation(const int nTest, const int nHunt, const int spa): noTests_(10000), noHunters_(10), spacing_(31){}

//Destructor
Monte_Carlo_Simulation_NS::Monte_Carlo_Simulation::~Monte_Carlo_Simulation(){}

//Getters
const int Monte_Carlo_Simulation_NS::Monte_Carlo_Simulation::NoTests_() const{    return noTests_;   }
const int Monte_Carlo_Simulation_NS::Monte_Carlo_Simulation::NoHunters_() const { return noHunters_; }
const int Monte_Carlo_Simulation_NS::Monte_Carlo_Simulation::Spacing_() const {   return spacing_;   }

//Do the simulation
void Monte_Carlo_Simulation_NS::Monte_Carlo_Simulation::simulate(){
    using namespace Linear_Spacing_NS;
    using namespace Matrix_NS;

    std::mt19937 mt( time(0) );

    Linear_Spacing lam(3, 8, Spacing_());      //lam.printVector();
    Linear_Spacing p(0.05, 0.95, Spacing_());  //p.printVector();
    Matrix res(Spacing_(), Spacing_(), 0);     //res.printMatrix();

    int numProcessor = omp_get_num_procs();
    #pragma omp parallel for num_threads(numProcessor)
    for(int kk = 0; kk < Spacing_(); kk++){
    //for(int kk = 0; kk < 4; kk++){
        for (int ll = 0; ll < Spacing_(); ll++ ){
        //for (int ll = 0; ll < 3; ll++ ){
            std::vector<double> tests(NoTests_(), 0);  //Initialize column vector of size (1,NoTests_()=10000) with zeros
            double totalHitDuck = 0;

            for (int mm = 0; mm< NoTests_(); mm++){
            //for (int mm = 0; mm< 6; mm++){
                std::poisson_distribution<int> pd(lam(kk));
                Matrix tmp(pd(mt), NoHunters_(), -99);
                //tmp.printMatrix();

                if (tmp.R_() == 0){
                    tests.at(mm) = 0;
                }
                else{
                    std::map<int, int> targets;
                    std::uniform_int_distribution<int> distribution(1, tmp.R_());

                    for(int vv = 0; vv<NoHunters_(); vv++){
                        int temp_vv = distribution(mt);
                        std::map<int, int>::iterator it = targets.find(temp_vv);
                        if( it == targets.end()){
                            targets.insert( std::make_pair(temp_vv, 1) );
                        }
                        else{
                            it->second++;
                        }
                    }

                    for( int nn=0; nn<tmp.R_(); nn++){
                        for(auto it=targets.begin(); it!=targets.end(); it++){
                            if(it->first == nn){
                                int number = it->second;
                                std::uniform_real_distribution<double> real_distr(0, 1);
                                for (int jkl=0; jkl<number; jkl++){
                                    tmp.M_( nn, jkl, real_distr(mt) );
                                }
                                number = 0;
                            } //if
                        }
                    } // nn
                    targets.clear();
                } //else
                //tmp.printMatrix();
                //std::cout << "p(ll):" << p(ll) << "\n";
                double hitDuck = 0;
                for (int in = 0; in < tmp.R_(); in++){
                    for (int ij = 0; ij< tmp.C_(); ij++){
                        if( tmp.M_().at(in).at(ij) == -99 ){
                            tmp.M_(in, ij, 0);
                        }
                        else if ( tmp.M_().at(in).at(ij) >= 0 && tmp.M_().at(in).at(ij) < p(ll) ){
                            tmp.M_(in, ij, 1);
                            hitDuck++;
                            break;
                        }
                        else {
                            tmp.M_(in, ij, 0);
                        }
                    }
                }

                //tmp.printMatrix();
                //Clear tmp
                for(int in=0; in<tmp.numel(); in++){
                    tmp(in, 0);
                }
                totalHitDuck += hitDuck;
                //std::cout << hitDuck << ","<< totalHitDuck << "\n";
                //tmp.printMatrix();
            } // mm
            double result = totalHitDuck/NoTests_();
            //double result = hitDuck/noTests;
            res.M_(kk, ll, result);
            tests.clear();
            //std::cout << "Res("<<kk<<","<<ll<<")= "<<res.M_().at(kk).at(ll) << "\n";
        }// ll
    }// kk
//    }//OMP
    res.printMatrix();

}
