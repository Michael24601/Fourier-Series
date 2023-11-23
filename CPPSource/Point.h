/******************************************************************************
 * Point.h
 * Author: Michael Saba
 * Date: 1/15/2023
 * Header file for the Point class, which describes coordinate points on a
 * 2D plane.
******************************************************************************/

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "unit.h"

namespace fs {
    /**************************************************************************
     * Point class definition.
     * Represents a coordinate point in a 2D cartesian system, like the 
     * complex plane.
    **************************************************************************/
    class Point{
    private: 

        real x;     //  Horizontal coordinate
        real y;     //  Vertical coordinate

    public:

        /**********************************************************************
         * No arg constructor.
         * Zero initializes x and y. 
        **********************************************************************/
        Point();

        /**********************************************************************
         * Argumented constructor.
         * Takes two reals as input, and sets x and y to their value.
        **********************************************************************/
        Point(real, real);

        real getX() const;  // Getter for x

        real getY() const;  // Getter for y
    
        void setX(real);    // Setter for x

        void setY(real);    // Setter for y  

        // Overloaded += operator
        Point& operator+=(const Point& point);

        // Overloaded *= operator
        Point& operator*=(real scale);

        // Overloaded /= operator
        Point& operator/=(real scale);

        // Overloaded comparison operator. Returns true if x and y match.
        bool operator==(const Point& right);
        
    };
}

/******************************************************************************
 * Overloaded output operator defined as a non-member function.
 * Takes out stream object and a constant reference to a Point object
 * as parameters (left and right operands). 
 * Displays "(x, y)". Returns the out stream object reference.
******************************************************************************/
std::ostream& operator<<(std::ostream&, const fs::Point&);

#endif