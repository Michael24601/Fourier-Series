/******************************************************************************
 * ComplexNumber.h
 * Header file for Complex number class.
******************************************************************************/

#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

#include <iostream>
#include <cmath>
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
         * All complex numbers are localted on a circle with its center on
         * the origin of the complex plane and a radius equal to the
         * magnitude or norm of the complex number.
         * This function returns the angle of number along the positive side
         * with the x axis.
         * The angle is in radians.
        **********************************************************************/
        real getAngle() const;

        /**********************************************************************
         * All complex numbers are localted on a circle with its center on
         * the origin of the complex plane and a radius equal to the
         * magnitude or norm of the complex number.
         * This function rotates the complex number along this circle the
         * given angle, and returns this as a new complex number, without
         * modifying the class member variables.
        **********************************************************************/
        ComplexNumber addAngleWithoutModifying(real angleToAdd) const;

        /**********************************************************************
         * All complex numbers are localted on a circle with its center on
         * the origin of the complex plane and a radius equal to the
         * magnitude or norm of the complex number.
         * This function rotates the complex number along this circle the
         * given angle, and modifies the object while doing so.
        **********************************************************************/
        void addAngle(real angleToAdd);

        /**********************************************************************
         * All complex numbers are localted on a circle with its center on
         * the origin of the complex plane and a radius equal to the
         * magnitude or norm of the complex number.
         * This function returns the magnitude.
        **********************************************************************/
        real getMagnitude() const;

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