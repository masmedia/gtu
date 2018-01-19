#include "Linear_Spacing.hpp"
 //Constructor
Linear_Spacing_NS::Linear_Spacing::Linear_Spacing(
                                                  const double high,
                                                  const double low,
                                                  const uint64_t space)
                                                  :    hVal_(high),
                                                       lVal_(low),
                                                       spacing_(space),
                                                       lin_spacing_(){
    if (high<low){
        std::swap(lVal_, hVal_);
    }

    const double increment = (hVal_-lVal_)/(spacing_ - 1);
    double temp = lVal_;

    for(int i=0; i<spacing_; i++){
        lin_spacing_.emplace_back(temp);
        temp += increment;
    }
}
//Destructor
Linear_Spacing_NS::Linear_Spacing::~Linear_Spacing(){   }
//Copy Constructor
Linear_Spacing_NS::Linear_Spacing::Linear_Spacing(const Linear_Spacing_NS::Linear_Spacing& other) : hVal_(other.hVal_),
                                                                                 lVal_(other.lVal_),
                                                                                 spacing_(other.spacing_),
                                                                                 lin_spacing_(){
    for(auto i = other.lin_spacing_.begin(); i != other.lin_spacing_.end(); ++i){
        lin_spacing_.emplace_back(*i);
    }
}
//Copy Assignment Operator
Linear_Spacing_NS::Linear_Spacing& Linear_Spacing_NS::Linear_Spacing::operator=(const Linear_Spacing& rhs){
    if (this != &rhs){
        this->lin_spacing_.clear();
        for(auto i = rhs.lin_spacing_.begin(); i != rhs.lin_spacing_.end(); ++i){
            this->lin_spacing_.emplace_back(*i);
        }
    }
    //assignment operator
    return *this;
}

//Member functions
//Getters and setters
const double Linear_Spacing_NS::Linear_Spacing::HVal_()const{  return hVal_;   }
const double Linear_Spacing_NS::Linear_Spacing::LVal_()const{  return lVal_;   }
const std::vector<double>& Linear_Spacing_NS::Linear_Spacing::LinSpa_()const{  return lin_spacing_;  }

//Operator overloading for reaching certain indexed element
double Linear_Spacing_NS::Linear_Spacing::operator()(const int i){
    return this->lin_spacing_[i];
}
//Prints vector
void Linear_Spacing_NS::Linear_Spacing::printVector(){
    std::cout << "\nPrinting the vector...\n";
    for(auto i = LinSpa_().begin(); i!= LinSpa_().end(); ++i){
        std::cout << *i << " ";
    }
    std::cout << "\nEnd of vector... \n";
}
