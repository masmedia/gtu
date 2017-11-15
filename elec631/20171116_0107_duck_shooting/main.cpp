#include <random>
#include <ctime>
#include <map>
#include "Linear_Spacing.hpp"
#include "Poisson.hpp"
#include "Matrix.hpp"

using namespace Poisson_NS;
using namespace Linear_Spacing_NS;
using namespace Matrix_NS;

int main(){

    const int noTests = 100;
    const int noHunters = 10;
    const int spacing = 31;

    std::mt19937 mt( time(0) );

    Linear_Spacing lam(3, 8, spacing);      //lam.printVector();
    Linear_Spacing p(0.05, 0.95, spacing);  //p.printVector();
    Matrix res(spacing, spacing, 0);

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
                    //std::uniform_int_distribution<int> distribution(0, tmp.R_());   //??????
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
                for (int in = 0; in < tmp.numel(); in++){
                    if( tmp(in) == -99 ){
                        tmp(in, 0);
                    }
                    else if ( tmp(in) >= 0 && tmp(in) < p(ll) ){
                        tmp(in, 1);     // TODO: Burada duplicationlar oluyor onlarý cikart
                        hitDuck++;
                    }
                    else {
                        tmp(in, 0);
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
    res.printBigMatrix();

  return 0;
}
