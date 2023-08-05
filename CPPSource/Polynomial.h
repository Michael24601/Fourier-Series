/******************************************************************************
 * Polynomial.h
 * Author: Michael Saba
 * Date: 1/15/2023
 * Header file for the Polynomial class, which descrives a polynomial
 * function.
******************************************************************************/
 
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include "unit.h"


namespace fs{

    /**************************************************************************
     * Polynomial class definition, described in terms of its
     * coefficients.
    **************************************************************************/ 
    class Polynomial{
    private:

        /**********************************************************************
         * Vector representing the coefficinets of a polynomial P(t), the ith 
         * element being the coefficient of t^i starting at i = 0;
        **********************************************************************/ 
        std::vector<real> coefficients;

        // Represents the Polynomial's degree. Is always the vector's size - 1
        int degree;      

    public:

        /**********************************************************************
         * No arg constructor.
         * Since a polynomial has at least a constant term, initilaizes the
         * vector with a single zero element.
        **********************************************************************/
        Polynomial();

        /**********************************************************************
         * Argumented constructor.
         * Takes a reference to a vector of numbers, and sets them as the
         * Polynomial's coefficients
        **********************************************************************/
        Polynomial(std::vector<real>&);
       
        /**********************************************************************
         * Getter for a coefficient, according to an index.
         * If the index does not exist, throws an exception.
        **********************************************************************/
        real getCoefficient(int) const;

        // Getter for the degree
        int getDegree() const;

        /**********************************************************************
         * Setter for all the coefficients.
         * Note that the degree of the polynomial might not exactly match
         * the size of the sent vector, as the degree of the polynomial
         * goes only up to the last none-zero coefficient.
        **********************************************************************/
        void setCoefficients(std::vector<real>&);

        /**********************************************************************
         * Sets the coefficient of only one term.
         * Here term refers to the exponent of x, whose coefficient this
         * function sets. If the term already has a coefficient in the class
         * (if the term <= degree), then it is modified, otherwise, the 
         * polynomial is extended to include it and any terms in between the
         * previously largest and the new, granted it is not 0.
        **********************************************************************/
        void setCoefficient(real, int);

        /**********************************************************************
         * Overloaded + operator.
         * Takes a reference to a polynomial object as an argument, and adds
         * it to the calling object. The addition is done element wise, up
         * until the minimum degree between the two objects. The returned
         * Polynomial object has the same degree as the maximum of the two,
         * but if the both have the same size, it is possible the largest
         * two terms will cancel each other out, resulting in a degree lower 
         * than both. The calling object is not modified.
        **********************************************************************/
        Polynomial operator+(const Polynomial&) const;

        /**********************************************************************
         * Overloaded - operator.
         * Takes a reference to a polynomial object as an argument, and
         * subtracts it from the calling object. The subtraction is done 
         * element wise, up until the minimum degree between the two objects. 
         * If the calling object has a higher degree, the result's degree
         * will match it, and vice versa. But if the two polynomials have the
         * same degree, it's possible the highest degree coefficients will 
         * cancel out each other, resulting in a degree lower than both.
         * The calling object is not modified.
        **********************************************************************/
        Polynomial operator-(const Polynomial&) const;

         /**********************************************************************
         * Overloaded * operator.
         * Takes a reference to a polynomial object as an argument, and
         * multiplies it with the calling object. Each coefficient on the 
         * right hand side is multiplied with each one on the left hand side.
         * Since the terms as a whole are multiplied, the degree changes.
         * For example, if element [i] and element [j] are multiplied, their
         * coefficients' multiplication in the resulting matrix will be
         * stored in element [i + j]. To that end, the degree of the new
         * polynomial is the sum of their degrees.
         * The calling object is not modified.
        **********************************************************************/
        Polynomial operator*(const Polynomial&) const;

        /**********************************************************************
         * Overloaded += operator.
         * Applies the same set of operations on the calling object and 
         * argument as the + operator, but modifies and returns the calling
         * object reference.
        **********************************************************************/
        Polynomial& operator+=(const Polynomial&);

        /**********************************************************************
         * Overloaded -= operator.
         * Applies the same set of operations on the calling object and 
         * argument as the - operator, but modifies and returns the calling
         * object reference.
        **********************************************************************/
        Polynomial& operator-=(const Polynomial&);

        /**********************************************************************
         * Overloaded *= operator.
         * Applies the same set of operations on the calling object and 
         * argument as the * operator, but modifies and returns the calling
         * object reference.
        **********************************************************************/
        Polynomial& operator*=(const Polynomial&);

        /**********************************************************************
         * Get value function.
         * Returns the value of the polynomial P(t) at a specific value of t.
         * For example, the value of x^2 + 1 at t = 2 is 5. 
         * The calculation is done in linear time.
        **********************************************************************/
        real getValue(real) const; 

    };
}

/******************************************************************************
 * Overloaded output operator defined as non-member function.
 * Takes out stream object and a constant reference to a Polynomial
 * object as parameters (left and right operands). 
 * Displays "coefficient[0] + coefficient[1] * t^1 + ...".
 * Returns the out stream object reference.
******************************************************************************/
std::ostream& operator<<(std::ostream&, const fs::Polynomial&);

#endif