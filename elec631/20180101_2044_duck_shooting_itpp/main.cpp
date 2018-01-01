#include <random>
#include <ctime>
#include <map>
#include "itpp/itbase.h"

int main(){
  using namespace itpp;

  const int noTests = 100;
  const int noHunters = 10;
  const int spacing = 31;
  
  std::mt19937 mt( time(0) );
  vec lam = linspace(3, 8, spacing);//  std::cout << lam << std::endl;
  vec p = linspace(0.05, 0.95, spacing);
  mat res(spacing, spacing);
  res.zeros();//  std::cout << res << std::endl;
  
  for(int kk = 0; kk < spacing; kk++){
        for (int ll = 0; ll < spacing; ll++ ){
          vec tests(noTests);
          tests.zeros();//   std::cout << tests << std::endl;
          
          double totalHitDuck = 0;
          
          for (int mm = 0; mm< noTests; mm++){
            std::poisson_distribution<int> pd(lam(kk));
            mat tmp(pd(mt), noHunters);
            tmp.ones();
            tmp *= -99; //std::cout << tmp << std::endl;
            
            if (tmp.rows() == 0){
              tests(mm)=0;
            }
            else{
              std::map<int, int> targets;
              std::uniform_int_distribution<int> distribution(1, tmp.rows());
              
              for(int vv = 0; vv<noHunters; vv++){
                int temp_vv = distribution(mt);
                std::map<int, int>::iterator it = targets.find(temp_vv);
                if( it == targets.end()){
                  targets.insert( std::make_pair(temp_vv, 1) );
                  
                }
                else{
                  it->second++;                  
                }                
              }//vv
              for( int nn=0; nn<tmp.rows(); nn++){
                for(auto it=targets.begin(); it!=targets.end(); it++){
                  if(it->first == nn){
                    int number = it->second;
                    std::uniform_real_distribution<double> real_distr(0, 1);
                    for (int jkl=0; jkl<number; jkl++){
                      tmp.set( nn, jkl, real_distr(mt) );                      
                    }
                    number = 0;                    
                  } //if                  
                }                
              } // nn
              targets.clear();
              
            }//else
            double hitDuck = 0;
                for (int in = 0; in < tmp.rows(); in++){
                  for (int ij = 0; ij< tmp.cols(); ij++){
                    if( tmp.get(in, ij) == -99 ){
                      tmp.set(in, ij, 0);
                    }
                    else if ( tmp.get(in, ij) >= 0 && tmp.get(in, ij) < p(ll) ){
                      tmp.set(in, ij, 1);
                      hitDuck++;
                      break;                      
                    }
                    else {
                      tmp.set(in, ij, 0);                      
                    }                    
                  }//ij
                }//in
                
                tmp.zeros();//  std::cout << tmp << std::endl;
                totalHitDuck += hitDuck;
            
          }// mm
          double result = totalHitDuck/noTests;
          res.set(kk, ll, result);
          tests.clear();
          
        }// ll
    }// kk
    std::cout << res << std::endl;
  
  return 0;
}
