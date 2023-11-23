/******************************************************************************
 * Source file for the BezierCurve class member functions.
******************************************************************************/

#include "BezierCurve.h"

using namespace fs;

// No arg constructor definition
BezierCurve::BezierCurve() : t0{0}, t1{1} {}


// Argumented constructor definition
BezierCurve::BezierCurve(std::vector<Point>& points, real t0, real t1){
    setTimeParameters(t0, t1);
    setPoints(points);
}


// Generate Polynomial function definition
Polynomial BezierCurve::generatePolynomial(Polynomial& p1, Polynomial& p2) {
    std::vector<real> vectorTemp{ -t0 / (t1 - t0), 1 / (t1 - t0) };
    Polynomial first{ vectorTemp };
    // Note that p1 and p2 can be points as well, not just lines
    Polynomial second{ p2 - p1 };
    return (first * second) + p1;
}


// Generate X and Y function defintion
void BezierCurve::generateXandY(){

    // Resizing the vector
    x.resize(points.size());
    y.resize(points.size());
    for(int i = 0; i < points.size(); i++){
        x[i].resize(points.size() - i);
        y[i].resize(points.size() - i);
    }

    // Generates the degree 0 polynomials (points)
    for(int i = 0; i < points.size(); i++){
        std::vector<real> xVector{points[i].getX()};
        std::vector<real> yVector{points[i].getY()};

        Polynomial xPolynomial(xVector);
        Polynomial yPolynomial(yVector);

        x[0][i] = xPolynomial;
        y[0][i] = yPolynomial;
    }

    // Generates the rest of the polynomials
    for(int i = 1; i < points.size(); i++){
        for(int j = 0; j < points.size() - i ; j++){
            x[i][j] = generatePolynomial(x[i-1][j], x[i-1][j+1]);
            y[i][j] = generatePolynomial(y[i-1][j], y[i-1][j+1]);
        }
    }
}


// Point Number getter function defintion 
int BezierCurve::getPointNumber() const{
    return points.size();
}


// Point getter function definiton
Point BezierCurve::getPoint(int index) const{
    if(index < 0 || index >= points.size()){
        throw std::invalid_argument("The index does not exist");
    }
    return points[index];
}


// X curve getter function definition
Polynomial BezierCurve::getX() const{
    if(x.size() > 0 && x[x.size()-1].size() > 0){
        return x[x.size() - 1][0];
    }
    else{
        throw std::out_of_range("The curve is empty");
    }
}


// Y curve getter function definition
Polynomial BezierCurve::getY() const{
    if(y.size() > 0 && y[y.size()-1].size() > 0){
        return y[y.size() - 1][0];
    }
    else{
        throw std::out_of_range("The curve is empty");
    }
}


// t0 function definition
real BezierCurve::getT0() const{
    return t0;
}


// t1 function definition
real BezierCurve::getT1() const{
    return t1;
}


// Set Time Parameters function definition
void BezierCurve::setTimeParameters(real t0, real t1){
    if(t0 >= t1){
        throw std::invalid_argument("t0 must be strictly smaller than t1");
        return;
    }
    this->t0 = t0;
    this->t1 = t1;

    // Regenerates the functions X and Y
    generateXandY();
}


// Set Points function definition
void BezierCurve::setPoints(std::vector<Point>& points){
    this->points.resize(points.size());
    for(int i = 0; i < points.size(); i++){
        this->points[i] = points[i];
    }
    
    // Regenerates the functions X and Y
    generateXandY();
} 


// Set Point function definition
void BezierCurve::setPoint(const Point& point, int index){
    if(index < 0 || index > points.size()){
        throw std::invalid_argument("The index does not exist");
        return;
    }

    Point temp{point};
    points.insert(points.begin() + index, temp);

    // Regenrates X and Y
    generateXandY();
}


// Add Point function definition
void BezierCurve::addPoint(const Point& point){

    // Invokes set point at the end of the vector
    setPoint(point, static_cast<int>(points.size()));
}

// Integrate function defintion
ComplexNumber BezierCurve::integrate(real dt, int n) const{
    
    real r{0}, i{0};

    // Divides area under curve into rectangles of width dt
    for(real t = t0; t <= t1; t += dt){
        r += getX().getValue(t) * cos(2 * PI * t * n) * dt 
            - getY().getValue(t) * sin(2 * PI * t * n) * dt;

        i += getX().getValue(t) * sin(2 * PI * t * n) * dt
            + getY().getValue(t) * cos(2 * PI * t * n) * dt;
    }
    ComplexNumber result(r, i);
    return result;
}

// Overloaded output operator<< function defintion
std::ostream& operator<<(std::ostream& out, const BezierCurve& curve){
    if(curve.getPointNumber() == 0){
        out << "The curve is empty\n";
    }
    else {
        out << "X(t) = " << curve.getX() << "\nY(t) = " 
            << curve.getY();
    }
    return out;
}