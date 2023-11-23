/******************************************************************************
 * Source file for the BezierCurveVector class member functions.
******************************************************************************/

#include "BezierCurveVector.h"

using namespace fs;

// No arg constructor definition
BezierCurveVector::BezierCurveVector() : interval{1} {}

// Argumented constructor definition
BezierCurveVector::BezierCurveVector(real interval) : interval{interval} {}

// getBezierCurve function definition
BezierCurve BezierCurveVector::getBezierCurve(int index) const{
    if(index < 0 || index >= bezierCurveVector.size()){
        throw std::invalid_argument("The index does not exist");
    }
    return bezierCurveVector[index];
}

// getInterval function definition
real BezierCurveVector::getInterval() const{
    return interval;
}

// getBezierCurveNumber function defintion
int BezierCurveVector::getBezierCurveNumber() const{
    return bezierCurveVector.size();
}

// addBezierCurve function defintion
void BezierCurveVector::addBezierCurve(const BezierCurve& bezierCurve){
    // If the curve is empty, it isn't added
    if(bezierCurve.getPointNumber() == 0){
        std::cerr << "Cannot add empty Bezier Curve\n";
    }
    // If the vector is empty, then addition is automatic
    else if(bezierCurveVector.size() == 0){
        BezierCurve newCurve{bezierCurve};
        newCurve.setTimeParameters(0, interval);
        bezierCurveVector.push_back(newCurve);
    }
    // If the last point in the vector matches the first point in the argument
    else if(bezierCurve.getPoint(0) == 
        bezierCurveVector[getBezierCurveNumber() - 1]
        .getPoint(bezierCurveVector[getBezierCurveNumber() - 1]
        .getPointNumber())){
        BezierCurve newCurve{bezierCurve};
        real startPoint = getBezierCurveNumber() * interval;
        newCurve.setTimeParameters(startPoint, startPoint + interval);
        bezierCurveVector.push_back(newCurve);
    }
    // Else we can't push the BezierCurve
    else{
         std::cerr << "Cannot add discontinuous Bezier Curve\n";
    }
}

void BezierCurveVector::addBezierCurve(std::vector<Point>& points){
    // If the curve is empty, it isn't added
    if(points.size() == 0){
        std::cerr << "Cannot add empty Bezier Curve\n";
    }
    // If the vector is empty, then addition is automatic
    else if(bezierCurveVector.size() == 0){
        BezierCurve curve(points, 0, interval);
        bezierCurveVector.push_back(curve);
    }
    // If the last point in the vector matches the first point in the argument
    else if(points[0] == 
        bezierCurveVector[getBezierCurveNumber() - 1]
        .getPoint(bezierCurveVector[getBezierCurveNumber() - 1]
        .getPointNumber() - 1)){
        real startPoint = getBezierCurveNumber() * interval;
        BezierCurve curve(points, startPoint, (startPoint + interval));
        bezierCurveVector.push_back(curve);
    }
    // Else we can't push the BezierCurve
    else{
         std::cerr << "Cannot add discontinuous Bezier Curve\n";
    }
}


// Integrate function definition
ComplexNumber BezierCurveVector::integrate(real dt, int n) const{
    ComplexNumber result{};
    for(int i = 0; i < bezierCurveVector.size(); i++){
        /**********************************************************************
         * Note that because the curve handles setting the time parameters
         * of the curves according to an interval, there is no need
         * to change anything here. If we want the integration to be 
         * between 0 and 1 for the total, we can set the interval to 
         * 1/n, instead of sending n/size here.
        **********************************************************************/
        result += bezierCurveVector[i].integrate(dt, n);
    }
    return result;
}

// Overloaded output operator<< function definition
std::ostream& operator<<(std::ostream& out, const BezierCurveVector& vector){
    if(vector.getBezierCurveNumber() == 0){
        out << "The vector is empty.";
    }
    else{
        for(int i = 0; i < vector.getBezierCurveNumber(); i++){
            out << "Bezier Curve [" << (i) << "]:\n" 
                << vector.getBezierCurve(i) << "\n";
        }
    }
    return out;
}