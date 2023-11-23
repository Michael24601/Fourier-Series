/******************************************************************************
 * Source file for the ComplexNumber class member functions.
******************************************************************************/

#include "ComplexNumber.h"

using namespace fs;

// No arg constructor definition
ComplexNumber::ComplexNumber() : r{0}, i{0} {}


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


real ComplexNumber::getAngle() const {
    return std::atan2(i, r);
}


ComplexNumber ComplexNumber::addAngleWithoutModifying(real angleToAdd) const {
    real magnitude = this->getMagnitude();
    real currentAngle = this->getAngle();

    real newAngle = currentAngle + angleToAdd;

    real newR = magnitude * std::cos(newAngle);
    real newI = magnitude * std::sin(newAngle);

    return ComplexNumber(newR, newI);
}


void ComplexNumber::addAngle(real angleToAdd) {
    real magnitude = this->getMagnitude();
    real currentAngle = this->getAngle();

    real newAngle = currentAngle + angleToAdd;

    this->r = magnitude * std::cos(newAngle);
    this->i = magnitude * std::sin(newAngle);
}


real ComplexNumber::getMagnitude() const{
    return std::sqrt(r * r + i * i);
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
    out << "(" << number.getReal() << " + " << number.getImaginary() << " * i)"; 
    return out;
}