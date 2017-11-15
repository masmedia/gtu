#include "Poisson.hpp"
#include <ctime>
//Default Constructor
Poisson_NS::Poisson::Poisson() : pVal_(0), mean_(4), mt_(time(0)), pd_(mean_){
    //std::cout << "Default constructor\t"<<pd_ <<std::endl;
    pVal_ = pd_(mt_);
}
//Constructor
Poisson_NS::Poisson::Poisson(const int mean) : pVal_(0),  mean_(mean), mt_(time(0)), pd_(mean_) {
    //std::cout << "Integer constructor called" << std::endl;
    pVal_ = pd_(mt_);
}
//Constructor
Poisson_NS::Poisson::Poisson(const double mean) : pVal_(0), mean_(mean), mt_(time(0)), pd_(mean_){
    //std::cout << "Double constructor called" << std::endl;
    pVal_ = pd_(mt_);
}

//Destructor
Poisson_NS::Poisson::~Poisson(){}

//Copy Constructor
Poisson_NS::Poisson::Poisson(const Poisson& other) : pVal_(other.pVal_), mean_(other.mean_), mt_(other.mt_), pd_(other.pd_){}

//Copy Assignment Operator
Poisson_NS::Poisson& Poisson_NS::Poisson::operator=(const Poisson& rhs){
    //handle non-self assignment
    if (this != &rhs){
        this->pVal_ = rhs.pVal_;
        this->mean_ = rhs.mean_;
        this->mt_ = rhs.mt_;
        this->pd_ = rhs.pd_;
    }
    return *this;
}
//Member functions
//Getters and Setters
const int Poisson_NS::Poisson::PVal(){                          return pVal_;       }
std::poisson_distribution<int>& Poisson_NS::Poisson::PD_(){     return pd_;         }
int Poisson_NS::Poisson::generatePVal(){                        return pd_(mt_);    }

//Member visualization function to check the distribution with Mersenne-Twister seeding
void Poisson_NS::Poisson::visualizeDistribution(const double meanVal){

    const int numExp = 10000;   // Number of experiments
    const int numStars = 100;   // Maximum number of stars to distribute

    std::mt19937 mert_(time(0));
    std::poisson_distribution<int> poisDist_(meanVal);

    int p[10]={};

    for (int i=0; i<numExp; ++i) {
        int number = poisDist_(mert_);
        if (number<10) ++p[number];
    }

    std::cout << "Poisson Distribution with mean " << meanVal << std::endl;
    for (int i=0; i<10; ++i)
        std::cout << i << ": " << std::string(p[i]*numStars/numExp,'*') << std::endl;
}

//Nonmember functions
//Operator overloading for <<
std::ostream& Poisson_NS::operator<<(std::ostream& o, const Poisson_NS::Poisson& p){
    Poisson_NS::Poisson temp = p;
    return o << temp.PD_();
}
