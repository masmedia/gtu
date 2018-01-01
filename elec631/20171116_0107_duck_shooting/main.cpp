#include <random>
#include <ctime>
#include <map>
#include <omp.h>
#include "Linear_Spacing.hpp"
#include "Matrix.hpp"
//#include "Poisson.hpp"

//using namespace Poisson_NS;

int main(){
    using namespace Linear_Spacing_NS;
    using namespace Matrix_NS;

    const int noTests = 10000;
    const int noHunters = 10;
    const int spacing = 31;

    std::mt19937 mt( time(0) );

    Linear_Spacing lam(3, 8, spacing);      //lam.printVector();
    Linear_Spacing p(0.05, 0.95, spacing);  //p.printVector();
    Matrix res(spacing, spacing, 0);

    int numProcessor = omp_get_num_procs();
    #pragma omp parallel for num_threads(numProcessor)
    for(int kk = 0; kk < spacing; kk++){
    //for(int kk = 0; kk < 4; kk++){
        for (int ll = 0; ll < spacing; ll++ ){
        //for (int ll = 0; ll < 3; ll++ ){
            std::vector<double> tests(noTests, 0);  //Initialize column vector of size (1,100) with zeros
            double totalHitDuck = 0;

            for (int mm = 0; mm< noTests; mm++){
            //for (int mm = 0; mm< 6; mm++){
                std::poisson_distribution<int> pd(lam(kk));
                Matrix tmp(pd(mt), noHunters, -99);
                //tmp.printMatrix();

                if (tmp.R_() == 0){
                    tests.at(mm) = 0;
                }
                else{
                    std::map<int, int> targets;
                    std::uniform_int_distribution<int> distribution(1, tmp.R_());

                    for(int vv = 0; vv<noHunters; vv++){
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
            double result = totalHitDuck/noTests;
            //double result = hitDuck/noTests;
            res.M_(kk, ll, result);
            tests.clear();
            //std::cout << "Res("<<kk<<","<<ll<<")= "<<res.M_().at(kk).at(ll) << "\n";
        }// ll
    }// kk
//    }//OMP
    res.printMatrix();

    return 0;
}
