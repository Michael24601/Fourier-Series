/******************************************************************************
 * BezierCurve.h
 * Header file for a Bezier Curve class. A bezier curve is a curve specified
 * using a start and end point, and any number (starting at 0) of control
 * points in the middle.
 * A line is a Bezier curve, where its shape is traced by moving uniformally
 * from the start point to the end point.
 * A quadratic Bezier Curve is one that has a single control point. It is
 * defined by first drawing the two lines between the start and control
 * point, and the control and end point, and then simultaneously moving two
 * points, one on each line, all while keeping track of the line drawn between
 * these two new points. During this interval of time, the path traced by
 * a point tarvelling along this new line is the quadratic bezier curve.
 * For the cubic curve, we just add another control point, and this time,
 * we get two new lines, and instead of tracing the path of the point along
 * one of them, we use two points, one for each line, draw yet another line
 * between them, and trace the path of a point along it.
 * This goes on for each degree we add.
 * This class defines the process by which we can get a parametric function
 * with an x(t) and y(t) component that are both polynomials of a degree
 * matching that of the bezier curve we are trying to model. The start and
 * end intervals of the functions (time t at which the polynomials x(t) and
 * y(t) are at the start point and end point respectively) are up to us to
 * choose, though the resulting functions will change depending on the
 * choice. 
******************************************************************************/

#ifndef BezierCurve_H
#define BezierCurve_H

#include <iostream>
#include <math.h>
#include <vector>
#include "Point.h"
#include "Polynomial.h"
#include "ComplexNumber.h"
#include "unit.h"

namespace fs{
    /**************************************************************************
     * Class definition of BezierCurve. Describes a bezier curve, a
     * parametric function of t whose x and y elements are polynomial
     * functions. The x and y elements can also be thought of as the real
     * and imaginary parts of the function.
     * A bezier curve is also defined by a series of points. Depending
     * on the number of points, the degree of each polynomial changes. For
     * instance, two points form a line which represents a degree 1
     * polynomial, so for n points, the polynomial are of degree n - 1.
     * This class is used to generate any degree of BezierCurves.
     * Usually, we would need no more than a cubic one (4 control points),
     * but the class itself allows for an arbitrary size.
    **************************************************************************/
    class BezierCurve{
    private:
        
        /**********************************************************************
         * Vector of pointers to the control points of the bezier curve.
         * There must at least be 2 points, the start and end. The rest are
         * control points.
        **********************************************************************/
        std::vector<Point> points;
        
        /**********************************************************************
         * 2D vectors of polynomials that describe the polynomials that
         * define the bezier curve. The 2D vector looks like a pyramid,
         * where the first vector contains m polynomials, the second
         * contains m - 1 ... etc.
         * The vectors are generated using the generatePolynomial function,
         * which starts with every consecutive pair of points (degree 0
         * polynomials) and generates the first wave of n - 1 lines (degree
         * 1 polynomials) working its way up to the degree n-1 polynomials,
         * and so forth.
        **********************************************************************/
        std::vector<std::vector<Polynomial>> x;     // x polynomials
        std::vector<std::vector<Polynomial>> y;     // y polynomials
        
        /**********************************************************************
         * When describing a curve parametrically, we can think of t as a
         * time variable, and as x(t) and y(t) changing as time passes. With
         * a bezier curve, we can generate x and y polynomials from the
         * control points, but while the control points specify a unique 
         * curve, the polynomials won't be unique unless we determine the
         * range of t, with t0 being the time x and y match the first control
         * point, and t1 being the time x and y match the last control point.
         * For instance, it can be from 0 to 1 seconds. Changing t0 and t1
         * changes the polynomials, since the curve has to match, but the
         * input's changed. 
        **********************************************************************/
        real t0;    // Input for which x and y match the first control point
        real t1;    // Input for which x and y match the last control point

        /**********************************************************************
         * Generate n degree polynomial from two (n-1) polynomials.
         * The function returns a new polynomial.
         * One way to understand what the newly generated polynomial is to
         * imagine a point traveling in constant speed from 
         * t = t0 and t = t1. There is also a second point with the same
         * attributes traveling over the second. Then imagine a moving
         * segment attaching the two points. If a third point with the same
         * constraints travels over this line. The polynomial it draws
         * is the generated one.  
        **********************************************************************/
        Polynomial generatePolynomial(Polynomial& p1, Polynomial& p2);

        /**********************************************************************
         * Generates the polynomials in the vectors x and y.
         * Used whenever there is a change in the points.
        **********************************************************************/
        void generateXandY();

    public:

        /**********************************************************************
         * No arg constructor.
         * Does not initialize the vector or polynpmial. The time tange
         * t0 to t1 is 0 to 1 by default.
        **********************************************************************/
        BezierCurve();

        /**********************************************************************
         * Argumented constructor.
         * Fills the points vector with the adresses in the argument. While
         * the argument's vector and calling object's vector are disticnt 
         * objects, they hold the addresses to the same points.
         * The constructor then generates the x and y polynomials.
        **********************************************************************/
        BezierCurve(std::vector<Point>&, real, real);

        /**********************************************************************
         * Getter for a control point in the curve.
         * Returns a point by value to limit access to the class's members.
        **********************************************************************/
        Point getPoint(int index) const;

        // Getter for number of points
        int getPointNumber() const;

        /**********************************************************************
         * Getter for the x polynomial.
         * Returns x by vaue to limit user access to the actual polynomial.
         * Note that only the topmost x polynomial in the 2D vector is
         * returned. 
        **********************************************************************/ 
        Polynomial getX() const; 
    
        /**********************************************************************
         * Getter for the y polynomial.
         * Returns y by vaue to limit user access to the actual polynomial.
         * Note that only the topmost x polynomial in the 2D vector is
         * returned.  
        **********************************************************************/ 
        Polynomial getY() const;

        real getT0() const;        // Getter for t0
    
        real getT1() const;        // Getter for t1

        /**********************************************************************
         * Setter for all the points of the curve.
         * If a vector already exists, replaces it.
         * Regenerates the x and y polynomials.
        **********************************************************************/
        void setPoints(std::vector<Point>&);

        /**********************************************************************
         * Setter for one of the control points.
         * point determines which point it is, and x and y determine where
         * to move the point to. This does not change the point's address by
         * creating a new object. That x and y are sent seperately 
         * reinforces that. If the point doesn't exist (the vector is 
         * smaller), than an out of bounds error is thrown.
        **********************************************************************/
        void setPoint(const Point& point, int index);

        /**********************************************************************
         * Adds a point to the BezierCurve. 
         * The address of the point is sent, so the object must already be
         * created and managed outside of the scope of this class. The point
         * is added at the end of the vector and bezier curve.
        **********************************************************************/
        void addPoint(const Point& point);

        /**********************************************************************
         * Setter for t0 and t1.
         * t0 is supposed to be strictly smaller, and an invalid argument
         * error is thrown otherwise.
         * x and y are recalculated.  
        **********************************************************************/
        void setTimeParameters(real t0, real t1);

        /**********************************************************************
         * Integrates the parametric function e^(pi * i * t * n) * f(t) 
         * with respect to t from t = t0 to t = t1.
         * The parametric function is interpreted as having a real part
         * x(t) + an imaginary part y(t). The exponential term is
         * e^(n * i * pi * t), which we may more easily write as 
         * cos(n * pi * t) + i * (n * pi * t).
         * So in reality, we are integrating the function F(t) =
         * x(t) * cos(n * pi * t) - y(t) * sin(n * pi * t) + 
         * i * (x(t) * sin(n * pi * t) + y(t) * cos(n * pi * t)).
         * Returns a complex number.
        **********************************************************************/
        ComplexNumber integrate(real dt, int n) const;
        
    };
}

/******************************************************************************
 * Overloaded output operator defined as a non member function.
 * Writes the curve in terms of X(t) and Y(t).
 * If the curve is empty, prints a message explaining that.
******************************************************************************/
std::ostream& operator<<(std::ostream&, const fs::BezierCurve&);

#endif