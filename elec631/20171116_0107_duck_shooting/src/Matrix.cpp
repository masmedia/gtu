#include <iomanip>  //For std::set(w)
#include "Matrix.hpp"
//Constructor
Matrix_NS::Matrix::Matrix(const uint64_t r, const uint64_t c) : row_(r), column_(c), defaultVal_(0){
    //std::cout << "\nConstructor1 is called...\n\n";
    createMatrix(r, c, 0);
}
//Constructor
Matrix_NS::Matrix::Matrix(const uint64_t r, const uint64_t c, const double val) : row_(r), column_(c), defaultVal_(val) {
    //std::cout << "\nConstructor2 is called...\n\n";
    createMatrix(r, c, val);
}
//Destructor
Matrix_NS::Matrix::~Matrix(){
    //std::cout << "\nDestructor is called...\n\n";
}

//Copy Constructor
Matrix_NS::Matrix::Matrix(const Matrix& other) : row_(other.row_), column_(other.column_), defaultVal_(other.defaultVal_){
    //std::cout << "\nCopy Constructor is called...\n\n";
    createMatrix(other.row_, other.column_, other.defaultVal_);
    for(uint64_t i =0; i<other.row_; i++){
        for (uint64_t j=0; j<other.column_; j++){
            this->matrix_.at(i).at(j) = other.matrix_.at(i).at(j);
        }
    }
}

//Copy Assignment Operator
Matrix_NS::Matrix& Matrix_NS::Matrix::operator=( Matrix& rhs){
    //std::cout << "\nCopy Assignment Operator is called...\n";
    // handle non-self assignment
    if (this != &rhs){
        this->row_=rhs.row_;
        this->column_ = rhs.column_;
        this->defaultVal_ = rhs.defaultVal_;

        for(uint64_t i=0; i<rhs.row_; i++){
            for (uint64_t j=0; j<rhs.column_; j++){
                this->matrix_.at(i).at(j) = rhs.matrix_.at(i).at(j);
            }
        }
    }
    return *this;
}

//Getters and setters
const uint64_t Matrix_NS::Matrix::R_() const {      return row_;                }
const uint64_t Matrix_NS::Matrix::C_() const {      return column_;             }
const uint64_t Matrix_NS::Matrix::numel() const {   return row_*column_;        }
const std::vector< std::vector<double> >& Matrix_NS::Matrix::M_() const {    return matrix_; }
Matrix_NS::Matrix& Matrix_NS::Matrix::M_(uint64_t row, uint64_t col, double val){
    matrix_.at(row).at(col) = val;
    return *this;
}

//Member operator overloading for column major matrix indexing
double Matrix_NS::Matrix::operator()(const uint64_t index){
    return matrix_.at( index%row_ ).at( index/row_ );
}

void Matrix_NS::Matrix::operator()(const uint64_t index, const double value){
    matrix_.at( index%row_ ).at( index/row_ ) = value;
}
//Member operator overloading for basic mathematic matrix operations
Matrix_NS::Matrix& Matrix_NS::Matrix::operator+(const Matrix& rhs){
    //std::cout << "Inside member + overloading...\n";
    for(uint64_t i=0; i<rhs.row_; i++){
        for(uint64_t j=0; j<rhs.column_; j++){
            this->matrix_.at(i).at(j) = this->matrix_.at(i).at(j) + rhs.matrix_.at(i).at(j);
        }
    }
    return *this;
}
//Matrix_NS::Matrix& Matrix_NS::Matrix::operator-(const Matrix& rhs){}
//Matrix_NS::Matrix& Matrix_NS::Matrix::operator*(const Matrix& rhs){
Matrix_NS::Matrix& Matrix_NS::Matrix::operator*(double scalar){
    //std::cout << "Inside member * overloading...\n";
    for(uint64_t i=0; i<this->row_; i++){
        for(uint64_t j=0; j<this->column_; j++){
            this->matrix_.at(i).at(j) = this->matrix_.at(i).at(j) * scalar;
        }
    }
    return *this;

}
//Matrix_NS::Matrix& Matrix_NS::Matrix::operator/(const Matrix& rhs){}

//Create matrix with desired values
const void Matrix_NS::Matrix::createMatrix(const uint64_t r, const uint64_t c, double val){
    this->matrix_.resize(r);
    for(uint64_t i=0; i<r; i++){
        this->matrix_.at(i).resize(c);
        for(uint64_t j=0; j<c; j++){
            this->matrix_.at(i).at(j) = val;
        }
    }
}
//Print matrix for debugging issues
const void Matrix_NS::Matrix::printMatrix() const{
    std::cout << "Printing matrix...\n";
    for(uint64_t i=0; i<row_; i++){
        for(uint64_t j=0; j<column_; j++){
            //std::cout  << matrix_.at(i).at(j) << " ";
            //std::cout <<std::fixed<< matrix_.at(i).at(j) << " ";
            std::cout << std::fixed << std::setw(5) << std::setprecision(3) << matrix_.at(i).at(j) << " ";
        }
        std::cout<< "\n";
    }
    std::cout << "End of matrix\n\n";
}
//Nonmember + operator overloading for adding a scalar  from left hand side to matrix
Matrix_NS::Matrix& Matrix_NS::operator+(double scalar, const Matrix& rhs){
//    std::cout << "\nInside nonmember + overloading...\n";
    Matrix temp(rhs);
//    temp.printMatrix();
    for(uint64_t i=0; i<temp.R_(); i++){
        for(uint64_t j=0; j<temp.C_(); j++){
            temp.M_(i, j, temp.M_().at(i).at(j)+scalar);
        }
    }
//    temp.printMatrix();
//    std::cout << "Returned from nonmember+ overload......\n\n";
    return temp;
}
// Nonmember * operator overloading for left multiplication
Matrix_NS::Matrix& Matrix_NS::operator*(double scalar, const Matrix& rhs){
//    std::cout << "Inside nonmember left * overloading...\n";
    Matrix temp(rhs);
//    temp.printMatrix();
    for(uint64_t i=0; i<temp.R_(); i++){
        for(uint64_t j= 0; j< temp.C_(); j++){
            temp.M_(i, j, temp.M_().at(i).at(j)*scalar);
        }
    }
//    temp.printMatrix();
//    std::cout << "Returned from nonmember* left overload......\n\n";
    return temp;
}

// Nonmember * operator overloading for right multiplication
Matrix_NS::Matrix& Matrix_NS::operator*(const Matrix& rhs, double scalar){
//    std::cout << "Inside nonmember right * overloading...\n";
    Matrix temp(rhs);
//    temp.printMatrix();
    for(uint64_t i=0; i<rhs.R_(); i++){
        for(uint64_t j= 0; j< rhs.C_(); j++){
//            double d = rhs.M_().at(i).at(j);
//            rhs.M_(i, j, d*scalar);
            temp.M_(i, j, temp.M_().at(i).at(j)*scalar);
        }
    }
//    temp.printMatrix();
//    std::cout << "Returned from nonmember* right overload......\n\n";
    return temp;
}
