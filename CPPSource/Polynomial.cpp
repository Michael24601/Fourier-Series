/******************************************************************************
 * Polynomial.cpp
 * Author: Michael Saba
 * Date: 1/15/2023
 * Source file for the Polynomial class member functions.
******************************************************************************/

#include "Polynomial.h"

using namespace fs;

// getValue function definition
real Polynomial::getValue(real t) const{
    real result{};  // Resultant value

    /**************************************************************************
     * Uses Horner's rule to calculate the value of the polynomial in linear
     * time, taking advantage of the fact thatthe polynomial can be written
     * as c[0] + x * (c[1] + x * (c[2] + x(...))).
    **************************************************************************/
    for(int i = degree; i >= 0; i--){
        result = coefficients[i] + t * result;
    }
    return result;
}


// No arg constructor definition
Polynomial::Polynomial() : degree{1}{
    /**************************************************************************
     * Every polynomial has at least a constant zero term, so the vector has 
     * size 1 by default. 
    **************************************************************************/
    coefficients.resize(1);
    coefficients[0] = 0;
}


// Argumented constructor definition
Polynomial::Polynomial(std::vector<real>& coefficients){
    // Calls setCoefficients which already defines this operation
    setCoefficients(coefficients);
}


// Getter for the coefficient definition
real Polynomial::getCoefficient(int index) const{
    if(index < 0 || index >= coefficients.size()){
        throw std::invalid_argument("The index does not exist");
    }
    return coefficients[index];
}


// Getter for the degree definition
int Polynomial::getDegree() const{
    return degree;
}


// Setter for the coefficients definition
void Polynomial::setCoefficients(std::vector<real>& coefficients){
    // Checks for zero factors multiplying the highest degree terms
    int size = coefficients.size();
    // Note that we stop at 1 not 0, since 0 is a degree 0 polynomial
    while(size > 1 && coefficients[size - 1] == 0){
        size--;
    }

    /**************************************************************************
     * Degree matches the exponent of the largest term, which is the largest
     * index in the zero based vector, so it's its size - 1.
    **************************************************************************/
    degree = size - 1;

    /**************************************************************************
     * Copies only up to the new found size, since trailing 0 terms don't 
     * affect the degree of the polynomial.
    **************************************************************************/
    this->coefficients.resize(size);
    for(int i = 0; i < size; i++){
        this->coefficients[i] = coefficients[i];
    }
}


// Setter for one coefficient definition
void Polynomial::setCoefficient(real coefficient, int degree){
    // Checks if the term exists or not
    if (degree <= this->degree){
        coefficients[degree] = coefficient;
    }
    // Expands the vector if degree is larger and the coefficient isn't 0
    else if (coefficient != 0){
        coefficients.resize(degree);
        coefficients[degree] = coefficient;
    }
}


// Overloaded + operator definition
Polynomial Polynomial::operator+(const Polynomial& right) const{
    /**************************************************************************
     * The result's degree is at most the larger degree of the two 
     * Polynomials. The size is that degree + 1.
    **************************************************************************/
    std::vector<real> result;
    result.resize(std::max(this->degree, right.degree) + 1);

    // Sums the elements from both polynomials until one runs out
    for(int i = 0; i <= std::max(this->degree, right.degree); i++){
        if(i > this->degree){
            result[i] = right.coefficients[i];
        }
        else if (i > right.degree){
            result[i] = this->coefficients[i];
        }
        else{
            result[i] = this->coefficients[i] + right.coefficients[i]; 
        }
    }

    // Constructor validates vector and gets rid of trailing zero terms
    Polynomial p(result);
    return p;
}


// Overloaded - operator definition
Polynomial Polynomial::operator-(const Polynomial& right) const{
    /**************************************************************************
     * The result's degree is at most the larger degree of the two 
     * Polynomials. The size is that degree + 1.
    **************************************************************************/
    std::vector<real> result;
    result.resize(std::max(this->degree, right.degree) + 1);

    // Subtracts the elements from both polynomials until one runs out
    for(int i = 0; i <= std::max(this->degree, right.degree); i++){
        if(i > this->degree){
            //  We hvae a negative sign because it's actually of 0 - right 
            result[i] = -right.coefficients[i];
        }
        else if (i > right.degree){
            result[i] = this->coefficients[i];
        }
        else{
            result[i] = this->coefficients[i] - right.coefficients[i]; 
        }
    }

    // Constructor validates vector and gets rid of trailing zero terms
    Polynomial p(result);
    return p;
}


// Overloaded * operator definition
Polynomial Polynomial::operator*(const Polynomial& right) const{
    // The result's degree is the sum of both polynomials'.
    std::vector<real> result;
    result.resize(this->degree + right.degree + 1);

    // Multiplies each term by the other
    for(int i = 0; i <= this->degree; i++){
        for(int j = 0; j <= right.degree; j++){
            // Uses += since the same index may be reached more than once
            result[i + j] += coefficients[i] * right.coefficients[j];
        }
    }
    Polynomial p(result);
    return p;
}


// Overloaded += operator definition
Polynomial& Polynomial::operator+=(const Polynomial& right){
    // Invokes overloaded + operator
    Polynomial p = *this + right;
    *this = p;
    return *this;
}

// Overloaded -= operator definition
Polynomial& Polynomial::operator-=(const Polynomial& right){
    // Invokes overloaded - operator
    Polynomial p = *this - right;
    *this = p;
    return *this;
}


// Overloaded *= operator definition
Polynomial& Polynomial::operator*=(const Polynomial& right){
    // Invokes overloaded * operator
    Polynomial p = *this * right;
    *this = p;
    return *this;
}

// Output operator overloading
std::ostream& operator<<(std::ostream& out, const Polynomial& p){
    // Always at least 1 coefficient 
    out << p.getCoefficient(0);
    for(int i = 1; i <= p.getDegree(); i++){
        out << " + " << p.getCoefficient(i) << "t^" << i;
    }
    out << "\n";
    return out;
}