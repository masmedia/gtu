#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
namespace Matrix_NS{
    class Matrix{
        private:
            int row_;
            int column_;
            double defaultVal_;
            std::vector< std::vector<double> > matrix_;

        public:
            /** Default constructor */
            Matrix(const int, const int);
            Matrix(const int, const int, const double);
            /** Default destructor */
            ~Matrix();

            /** Copy constructor
             *  \param other Object to copy from
             */
            Matrix(const Matrix& other);

            /** Assignment operator
             *  \param other Object to assign from
             *  \return A reference to this
             */
            Matrix& operator=(Matrix& other);

            int R_() const;
            int C_() const;
            /** Number of elements stored in matrix. Gives row*column size */
            int numel() const;
            const std::vector< std::vector<double> >& M_() const;
            Matrix& M_(int, int, double);

            /** Overloading of operator for column major indexing */
            double operator()(const int);
            void operator()(const int, const double);

            /** Overloading the basic mathematical operators */
            Matrix& operator+(const Matrix& other);        // Works with mat1 + mat2
//            Matrix& operator-(const Matrix& other);
//            Matrix& operator*(const Matrix& other);      // Works with mat1 * mat2
            Matrix& operator*(double);                     // Works with mat1 * scalar
//            Matrix& operator/(const Matrix& other);

            /** Helper method for creation of matrix */
            void createMatrix(const int, const int, double);

            /** Print matrix for debugging*/
            void printMatrix();
            void printBigMatrix();
    };
    Matrix& operator+(double, const Matrix& other);  // Works with constant + mat1
    Matrix& operator*(double, const Matrix& other);  // Works with constant * mat1 (aka Left Multiplication)
    Matrix& operator*(const Matrix& other, double);  // Works with mat1 * constant (aka Right Multiplication)
}
#endif // MATRIX_H
