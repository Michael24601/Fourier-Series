/******************************************************************************
 * ComplexNumber.h
 * Author: Michael Saba
 * Date: 2/16/2023
 * Header file for the Complex Number class.
******************************************************************************/

#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

#include <iostream>
#include "unit.h"


namespace fs {
    /**************************************************************************
     * Complex Number class definition.
    **************************************************************************/
    class ComplexNumber{
    private: 

        real r;     //  Real part
        real i;     //  Imaginary part

    public:

        /**********************************************************************
         * No-arg constructor.
         * Sets the real and imaginary parts as 0.
        **********************************************************************/
        ComplexNumber();

        ComplexNumber(real r, real i);      // Argumented Constructor

        real getReal() const;       // Getter for the real component
        
        real getImaginary() const;  // Getter for the imaginary component

        void setReal(real r);       // Setter for the real component

        void setImaginary(real i);  // Setter for the imaginary component

        /**********************************************************************
         * Overloaded + operator
         * Caluclates and returns the sum of two complex numbers;
         * it is a complex number with the sum of the two real parts as its 
         * real component and the sum of the two imaginary parts as its 
         * imaginary component.
        **********************************************************************/
        ComplexNumber operator+(const ComplexNumber&) const;

        /**********************************************************************
         * Overloaded += operator
         * Caluclates and returns the sum of two complex numbers;
         * it is a complex number with the sum of the two real parts as its 
         * real component and the sum of the two imaginary parts as its 
         * imaginary component. Also updates the value of the calling object
         * which is returned.
        **********************************************************************/
        ComplexNumber& operator+=(const ComplexNumber&);

        /**********************************************************************
         * Overloaded * operator
         * Caluclates and returns the product of two complex numbers;
         * it is a complex number with the product of the two real parts -
         * the product of the imaginary parts as its real component and the 
         * sum of the product of the opposing parts parts as its imaginary 
         * component.
        **********************************************************************/
        ComplexNumber operator*(const ComplexNumber&) const;

         /**********************************************************************
         * Overloaded *= operator
         * Caluclates and returns the product of two complex numbers;
         * it is a complex number with the product of the two real parts as 
         * its real component and the product of the two imaginary parts as
         * its imaginary component. Also updates the value of the calling 
         * object which is returned.
        **********************************************************************/
        ComplexNumber& operator*=(const ComplexNumber&);

        /**********************************************************************
         * Overloaded / operator
         * Caluclates and returns the result of dividing a complex number
         * by a real; the real and imaginary parts are individually divided
         * by the real.
        **********************************************************************/
        ComplexNumber operator/(real) const;

        /**********************************************************************
         * Overloaded /= operator
         * Caluclates and returns the result of dividing a complex number
         * by a real; the real and imaginary parts are individually divided
         * by the real. Also updates the value of the calling 
         * object which is returned.
        **********************************************************************/
        ComplexNumber& operator/=(real);

    };
}

/******************************************************************************
 * Overloaded output operator defined as a non-member function.
 * Takes out stream object and a constant reference to a ComplexNumber 
 * object as parameters (left and right operands). 
 * Displays "real + <imaginary>i". Returns the out stream object 
 * reference.
******************************************************************************/
std::ostream& operator<<(std::ostream&, const fs::ComplexNumber&);

#endif