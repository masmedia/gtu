#ifndef MATRIX_H_20171115_2235
#define MATRIX_H_20171115_2235
#include <iostream>
#include <vector>
namespace Matrix_NS{
    class Matrix{
        private:
            uint64_t row_;
            uint64_t column_;
            double defaultVal_;
            std::vector< std::vector<double> > matrix_;

        public:
            /** Default constructor */
            Matrix(const uint64_t, const uint64_t);
            Matrix(const uint64_t, const uint64_t, const double);
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

            const uint64_t R_() const;
            const uint64_t C_() const;
            /** Number of elements stored in matrix. Gives row*column size */
            const uint64_t numel() const;
            const std::vector< std::vector<double> >& M_() const;
            Matrix& M_(uint64_t, uint64_t, double);

            /** Overloading of operator for column major indexing */
            double operator()(const uint64_t);
            void operator()(const uint64_t, const double);

            /** Overloading the basic mathematical operators */
            Matrix& operator+(const Matrix& other);        // Works with mat1 + mat2
//            Matrix& operator-(const Matrix& other);
//            Matrix& operator*(const Matrix& other);      // Works with mat1 * mat2
            Matrix& operator*(double);                     // Works with mat1 * scalar
//            Matrix& operator/(const Matrix& other);

            /** Helper method for creation of matrix */
            const void createMatrix(const uint64_t, const uint64_t, double);

            /** Print matrix for debugging*/
            const void printMatrix() const;
    };
    Matrix& operator+(double, const Matrix& other);  // Works with constant + mat1
    Matrix& operator*(double, const Matrix& other);  // Works with constant * mat1 (aka Left Multiplication)
    Matrix& operator*(const Matrix& other, double);  // Works with mat1 * constant (aka Right Multiplication)
}
#endif // MATRIX_H_20171115_2235
