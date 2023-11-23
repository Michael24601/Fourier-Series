/******************************************************************************
 * BezierCurveVector.h
 * Header file for a vector of consecutive bezier curves.
 * Here consecutive means two things: When one curve starts at t=t0 and ends
 * at t=t1, the curve after it must start at t=t1. And if a curve ends at
 * a point (x1, y1), the next curve must start at the same point, for
 * continuity.
 * With that, the curves now form a piece-wise function from t0 to tn.
 * For simplicity, we start the time at t = 0, and give each curve an equal
 * amount of time (interval). 
******************************************************************************/

#ifndef BEZIER_CURVE_VECTOR_H
#define BEZIER_CURVE_VECTOR_H

#include <iostream>
#include <math.h>
#include <vector>
#include "Point.h"
#include "BezierCurve.h"
#include "ComplexNumber.h"
#include "unit.h"

namespace fs{
    /**************************************************************************
     * Class definition of BezierCurveVector, a class that defines a
     * construct which holds a series of connected bezier curves defined
     * between t0 and t1.
     * Note that the time allocated to each curve is the same, so the
     * interval t0, t1 is divided evenly.
    **************************************************************************/
    class BezierCurveVector{
    private:

        // Vector holding connected Bezier Curves
        std::vector<BezierCurve> bezierCurveVector;

        /********************************************************************** 
         * Interval of time for which each BezierCurve is defined.
         * For example, if interval is 1, then the first Bezier Curve.
         * would be defined from t = 0 to t = 1, and the second from t = 1 to
         * t = 2 etc...
        **********************************************************************/
        real interval; 

    public:

        // No arg constructor, sets interval to 1 and keeps the vector empty
        BezierCurveVector();

        // Argumented constructor
        BezierCurveVector(real interval);

        /**********************************************************************
         * Returns the Bezier Curve by value at a specific index.
         * It is returned by value to avoid allowing the Bezier Curve to 
         * be changed after it has been placed.
         * The index must be whithin the range of Existing Bezier Curves.
        **********************************************************************/
        BezierCurve getBezierCurve(int index) const;

        // getBezierCurveNumber returns the number of Bezier Curves
        int getBezierCurveNumber() const;

        // getInterval, returns the time interval
        real getInterval() const;

        /**********************************************************************
         * Add a Bezier Curve at the end of the vector. 
         * The first point in the curve must match the last point in the 
         * previous Bezier Curve, or it won't be added.
         * The bezierCurve is sent by reference and copied internally 
         * if it fits the criteria, otherwise no copy is made.
         * The new BezierCurve must not be empty, or it won't be added.
         * The time parameters of the curve are set and managed.
        **********************************************************************/
        void addBezierCurve(const BezierCurve& bezierCurve);

        /**********************************************************************
         * Add a Bezier Curve at the end of the vector.
         * This time, takes an array of points
         * The first point in the curve must match the last point in the 
         * previous Bezier Curve, or it won't be added.
         * The bezierCurve is sent by reference and copied internally 
         * if it fits the criteria, otherwise no copy is made.
         * The new BezierCurve must not be empty, or it won't be added.
         * The time parameters of the curve are set and managed.
        **********************************************************************/
        void addBezierCurve(std::vector<Point>& points);

        // Interval setter, recalculates each Bezier Curve. Muts be positive
        void setInterval(real interval);

        /**********************************************************************
         * Integrates the parametric function * e^(pi * i * t * n) * f(t) 
         * with respect to t from t = 0 to t = vector_size * interval.
         * The function is a Piece-Wise defined function, where for 
         * inputs t = 0 to 1, it is the first BezierCurve, then the second
         * for 1 to 2 ... etc.
         * The parametric function is interpreted as having a real part
         * x(t) + an imaginary part y(t). The exponential term is
         * e^(n * i * pi * t), which we may more easily write as 
         * cos(n * pi * t) + i * (n * pi * t).
         * So in reality, we are integrating the function F(t) =
         * x(t) * cos(n * pi * t) - y(t) * sin(n * pi * t) + 
         * i * (x(t) * sin(n * pi * t) + y(t) * cos(n * pi * t)).
         * Each part of the function is intergated seperately then summed, 
         * since they are undefined in the other intervals of t.
         * Returns a complex number.
        **********************************************************************/
        ComplexNumber integrate(real dt, int n) const;

    };
}

/******************************************************************************
 * Overloaded output operator defined as a non-member function.
 * Ouputs each bezier curve in the vector.
 * If the vector is empty, prints a message saying that.
******************************************************************************/
std::ostream& operator<<(std::ostream&, const fs::BezierCurveVector&);

#endif