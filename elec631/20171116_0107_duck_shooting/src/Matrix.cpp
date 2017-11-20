#include <iomanip>  //For std::set(w)
#include "Matrix.hpp"
//Constructor
Matrix_NS::Matrix::Matrix(const int r, const int c) : row_(r), column_(c), defaultVal_(0){
    //std::cout << "\nConstructor1 is called...\n\n";
    createMatrix(r, c, 0);
}
//Constructor
Matrix_NS::Matrix::Matrix(const int r, const int c, const double val) : row_(r), column_(c), defaultVal_(val) {
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
    for(int i =0; i<other.row_; i++){
        for (int j=0; j<other.column_; j++){
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

        for(int i=0; i<rhs.row_; i++){
            for (int j=0; j<rhs.column_; j++){
                this->matrix_.at(i).at(j) = rhs.matrix_.at(i).at(j);
            }
        }
    }
    return *this;
}

//Getters and setters
const int Matrix_NS::Matrix::R_()const {      return row_;                }
const int Matrix_NS::Matrix::C_()const {      return column_;             }
const int Matrix_NS::Matrix::numel() const{   return row_*column_;        }
const std::vector< std::vector<double> >& Matrix_NS::Matrix::M_()const{    return matrix_; }
Matrix_NS::Matrix& Matrix_NS::Matrix::M_(int row, int col, double val){
    matrix_.at(row).at(col) = val;
    return *this;
}

//Member operator overloading for column major matrix indexing
double Matrix_NS::Matrix::operator()(const int index){
    return matrix_.at( index%row_ ).at( index/row_ );
}

void Matrix_NS::Matrix::operator()(const int index, const double value){
    matrix_.at( index%row_ ).at( index/row_ ) = value;
}
//Member operator overloading for basic mathematic matrix operations
Matrix_NS::Matrix& Matrix_NS::Matrix::operator+(const Matrix& rhs){
    //std::cout << "Inside member + overloading...\n";
    for(int i=0; i<rhs.row_; i++){
        for(int j=0; j<rhs.column_; j++){
            this->matrix_.at(i).at(j) = this->matrix_.at(i).at(j) + rhs.matrix_.at(i).at(j);
        }
    }
    return *this;
}
//Matrix_NS::Matrix& Matrix_NS::Matrix::operator-(const Matrix& rhs){}
//Matrix_NS::Matrix& Matrix_NS::Matrix::operator*(const Matrix& rhs){
Matrix_NS::Matrix& Matrix_NS::Matrix::operator*(double scalar){
    //std::cout << "Inside member * overloading...\n";
    for(int i=0; i<this->row_; i++){
        for(int j=0; j<this->column_; j++){
            this->matrix_.at(i).at(j) = this->matrix_.at(i).at(j) * scalar;
        }
    }
    return *this;

}
//Matrix_NS::Matrix& Matrix_NS::Matrix::operator/(const Matrix& rhs){}

//Create matrix with desired values  (TRUE)
void Matrix_NS::Matrix::createMatrix(const int r, const int c, double val){
    this->matrix_.resize(r);
    for(int i=0; i<r; i++){
        this->matrix_.at(i).resize(c);
        for(int j=0; j<c; j++){
            this->matrix_.at(i).at(j) = val;
        }
    }
}
//Print matrix for debugging issues
void Matrix_NS::Matrix::printMatrix(){
    std::cout << "Printing matrix...\n";
    for(int i=0; i<row_; i++){
        for(int j=0; j<column_; j++){
            //std::cout  << matrix_.at(i).at(j) << " ";
            //std::cout <<std::fixed<< matrix_.at(i).at(j) << " ";
            std::cout <<std::setw(10) << matrix_.at(i).at(j) << " ";
        }
        std::cout<< "\n";
    }
    std::cout << "End of matrix\n\n";
}
// Print bigger matrices for debugging issues
void Matrix_NS::Matrix::printBigMatrix(){
    std::cout << "Printing matrix...\n";
    for(int i=0; i<row_; i++){
        for(int j=0; j<column_; j++){
            std::cout <<std::setw(5) << matrix_.at(i).at(j) << " ";
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
    for(int i=0; i<temp.R_(); i++){
        for(int j=0; j<temp.C_(); j++){
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
    for(int i=0; i<temp.R_(); i++){
        for(int j= 0; j< temp.C_(); j++){
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
    for(int i=0; i<rhs.R_(); i++){
        for(int j= 0; j< rhs.C_(); j++){
//            double d = rhs.M_().at(i).at(j);
//            rhs.M_(i, j, d*scalar);
            temp.M_(i, j, temp.M_().at(i).at(j)*scalar);
        }
    }
//    temp.printMatrix();
//    std::cout << "Returned from nonmember* right overload......\n\n";

    return temp;
}
