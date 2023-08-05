/******************************************************************************
 * ComplexNumber.cpp
 * Author: Michael Saba
 * Date: 2/17/2023
 * Source file for the ComplexNumber class member functions.
******************************************************************************/

#include "ComplexNumber.h"

using namespace fs;

// No arg constructor definition
ComplexNumber::ComplexNumber() : r{}, i{} {}


// Argumented constructor definition 
ComplexNumber::ComplexNumber(real r, real i) : r{r}, i{i} {}


// Real part getter definition
real ComplexNumber::getReal() const{
    return r;
}


// Imaginary part getter definition
real ComplexNumber::getImaginary() const{
    return i;
}


// Real part setter definition
void ComplexNumber::setReal(real r){
    this->r = r;
}


// Imaginary part setter definition
void ComplexNumber::setImaginary(real i){
    this->i = i;
}


// Overloaded + operator function definition
ComplexNumber ComplexNumber::operator+(const ComplexNumber& right) const{
    ComplexNumber temp{r + right.r, i + right.i};
    return temp;
}

// Overloaded += operator funciton definition
ComplexNumber& ComplexNumber::operator+=(const ComplexNumber& right){
    *this = *this + right;
    return *this;
}

// Overloaded * operator function definition
ComplexNumber ComplexNumber::operator*(const ComplexNumber& right) const{
    ComplexNumber temp{r * right.r - i * right.i, 
        r * right.i + i * right.r};
    return temp;
}

// Overloaded *= operator funciton definition
ComplexNumber& ComplexNumber::operator*=(const ComplexNumber& right){
    *this = *this * right;
    return *this;
}

// Overloaded / operator function definition
ComplexNumber ComplexNumber::operator/(real right) const{
    ComplexNumber temp{r / right, i / right};
    return temp;
}

// Overloaded /= operator funciton definition
ComplexNumber& ComplexNumber::operator/=(real right){
    *this = *this / right;
    return *this;
}

// Overloaded output operator definition
std::ostream& operator<<(std::ostream& out, const ComplexNumber& number){
    out << number.getReal() << ", " << number.getImaginary() << "i"; 
    return out;
}