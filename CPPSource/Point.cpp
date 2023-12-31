/******************************************************************************
 * Source file for the Point class member functions.
******************************************************************************/

#include "Point.h"

using namespace fs;

// No arg constructor definition.
Point::Point() : x{}, y{} {}


// Argumented constructor definition 
Point::Point(real x, real y) : x{x}, y{y} {}


// x getter definition
real Point::getX() const{
    return x;
}


// y getter definition
real Point::getY() const{
    return y;
}


// x setter definition
void Point::setX(real x){
    this->x = x;
}


// y setter definition
void Point::setY(real y){
    this->y = y;
}


Point& Point::operator+=(const Point& point){
    this->x += point.x;
    this->y += point.y;
    return *this;
}


Point& Point::operator*=(real scale){
    this->x *= scale;
    this->y *= scale;
    return *this;
}


Point& Point::operator/=(real scale){
    this->x /= scale;
    this->y /= scale;
    return *this;
}


bool Point::operator==(const Point& right){
    return (x == right.x && y == right.y);
}


// Overloaded output operator definition
std::ostream& operator<<(std::ostream& out, const Point& point){
    out << "(" << point.getX() << ", " << point.getY() << ")"; 
    return out;
}