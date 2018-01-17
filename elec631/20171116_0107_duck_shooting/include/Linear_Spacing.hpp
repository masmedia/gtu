#ifndef LINEAR_SPACING_H_20171031_1822
#define LINEAR_SPACING_H_20171031_1822
#include <iostream>
#include <vector>
namespace Linear_Spacing_NS{
    class Linear_Spacing{
        private:
            double hVal_;
            double lVal_;
            int spacing_;
            std::vector<double> lin_spacing_;

        public:
            /** Default constructor */
            Linear_Spacing(double, double, const int);

            /** Default destructor */
            ~Linear_Spacing();

            /** Copy constructor
            *  \param other Object to copy from
            */

            Linear_Spacing(const Linear_Spacing& other);
            /** Assignment operator
            *  \param other Object to assign from
            *  \return A reference to this
            */
            Linear_Spacing& operator=(const Linear_Spacing& other);

            /** Getters and setters*/
            const double HVal_() const;
            const double LVal_() const;
            const std::vector<double>& LinSpa_() const;

            /** Operator overload for () to reach certain element in the vector*/
            double operator()(const int);

            /** Prints vector for ease of debugging */
            void printVector();
    };  //End of Linear_Spacing class
}       //End of Linear_Spacing_NS namespace
#endif // LINEAR_SPACING_H_20171031_1822
