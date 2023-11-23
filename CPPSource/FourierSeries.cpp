/******************************************************************************
 * Source file for the FourierSeries class member functions.
******************************************************************************/

#include "FourierSeries.h"

using namespace fs;


FourierSeries::FourierSeries() {}


std::string FourierSeries::parseSVG(const std::string& filePath) const {

    std::ifstream svgFile(filePath); // Open the SVG file

    if (!svgFile.is_open()) {
        return "";
    }

    std::string svgContent((std::istreambuf_iterator<char>(svgFile)), 
        std::istreambuf_iterator<char>());
    svgFile.close(); // Close the SVG file

    size_t start = svgContent.find("d=\"M") + 3; 
    size_t end = svgContent.find("\"", start); 

    if (start != std::string::npos && end != std::string::npos) {
        std::string pathData = svgContent.substr(start, end - start);
        return pathData;
    }

    return "";
}


std::vector<std::vector<Point>> FourierSeries::parseSVGPath(
    const std::string& pathData) const {

    std::vector<std::vector<Point>> vectorOfPoints;

    // Create a string stream from the SVG path data
    std::istringstream pathStream(pathData);

    char command;
    double x, y;
    Point temp;

    while (pathStream >> command) {

        std::vector<Point> points;

        switch (command) {
            case 'M':
                pathStream >> x >> y; 
                temp = Point(x, y);
                break;
            case 'L':
                /**************************************************************
                 * First point in Bezier curve is the last point in the last
                 * curve.
                **************************************************************/ 
                points.push_back(temp);
                pathStream >> x >> y;
                // Get a new temp
                temp = Point(x, y);
                points.push_back(temp);
                vectorOfPoints.push_back(points);
                break;
            case 'Q':
                points.push_back(temp);
                pathStream >> x >> y;
                temp = Point(x, y);
                points.push_back(temp);
                pathStream >> x >> y;
                temp = Point(x, y);
                points.push_back(temp);
                vectorOfPoints.push_back(points);
                break;
            case 'C':
                points.push_back(temp);
                pathStream >> x >> y;
                temp = Point(x, y);
                points.push_back(temp);
                pathStream >> x >> y;
                temp = Point(x, y);
                points.push_back(temp);
                pathStream >> x >> y;
                temp = Point(x, y);
                points.push_back(temp);
                vectorOfPoints.push_back(points);
                break;
            case 'z':
                // End of the path
                break;
            default:
                break;
        }
    }

    return vectorOfPoints;
}



void FourierSeries::movePointsToMinimizeDistance(
    std::vector<std::vector<Point>>& points
) const {
    // First we find the bounding box of the points
    real minX = std::numeric_limits<real>::max();
    real minY = std::numeric_limits<real>::max();
    real maxX = std::numeric_limits<real>::lowest();
    real maxY = std::numeric_limits<real>::lowest();

    for (const auto& innerVector : points) {
        for (const auto& point : innerVector) {
            minX = std::min(minX, point.getX());
            minY = std::min(minY, point.getY());
            maxX = std::max(maxX, point.getX());
            maxY = std::max(maxY, point.getY());
        }
    }

    /**************************************************************************
     * Then we move the image such that the bounding box is centered at the
     * origin.
    **************************************************************************/  
    Point offset(-(maxX + minX)/2, -(maxY + minY)/2);

    // Apply the offset to move all points
    for (auto& innerVector : points) {
        for (auto& point : innerVector) {
            point += offset;
        }
    }
}


real FourierSeries::findMaxAbsolutePoint(
    const std::vector<std::vector<Point>>& points
) const {

    fs::Point maxAbsolutePoint = {
        -std::numeric_limits<float>::infinity(), 
        -std::numeric_limits<float>::infinity() 
    };

    for (const auto& innerVector : points) {
        for (const auto& point : innerVector) {
            maxAbsolutePoint.setX( 
                std::max(maxAbsolutePoint.getX(), std::abs(point.getX())));
            maxAbsolutePoint.setY(
                std::max(maxAbsolutePoint.getY(), std::abs(point.getY())));
        }
    }

    /**************************************************************************
     * Returns the larger of the two (x or y) as that will be the furthest 
     * the image goes.
    **************************************************************************/
    return std::max(maxAbsolutePoint.getX(), maxAbsolutePoint.getY());
}


void FourierSeries::scalePoints(
    std::vector<std::vector<Point>>& points, real size) const {

    // First, we find the maximum absolute point
    real maxAbsolutePoint = findMaxAbsolutePoint(points);

    /**************************************************************************
     * We then calculate the scaling factor needed to fit the image in a 
     * canvas with the specified size.
     * The size is divided by 2 because it describes the total width on either
     * side of the origin.
    **************************************************************************/
    real scale = (size/2) / maxAbsolutePoint;

    // Gives a 20% wiggle room for the image.
    scale *= 0.8;

    // We then uniformally scale all of the points
    for (auto& innerVector : points) {
        for (auto& point : innerVector) {
            point *= scale;
        }
    }
}


BezierCurveVector FourierSeries::generateBezierCurveVector(
    std::vector<std::vector<Point>> points
) const {
    /**************************************************************************
     * Interval set in such a way as to allow the animation to fully take
     * place between 0 and 1 seconds. This makes it easy so then speed up and
     * slow down later.
    **************************************************************************/ 
    real interval = 1.0/points.size();
    BezierCurveVector vector(interval);
    for(auto i = 0; i < points.size(); i++){
        vector.addBezierCurve(points[i]);
    }
    return vector;
}


std::vector<ComplexNumber> FourierSeries::generateCircles(real dt, int n,
    const BezierCurveVector& h) const {

    std::vector<ComplexNumber> circles;
    // First generates the circle with rotation speed 0.
    ComplexNumber c = h.integrate(dt, 0);
    circles.push_back(c);

    for(int i = 1; i < n; i++){
        if(i % 2 == 1){
            /******************************************************************
             * Odd complex coefficients are c[1], c[2] ... which need -1 and
             * -2 as n to cancel the vector's movement and get its value.
            ******************************************************************/
            c = h.integrate(dt , -(i/2 + 1));
        }
        else if(i % 2 == 0){
            /******************************************************************
             * Even complex coefficients are c[-1], c[-2] ... which need 1
             * and 2 as n to cancel the vector's movement and get its value.
            ******************************************************************/
            c = h.integrate(dt, i/2);
        }
        circles.push_back(c);
    }
    return circles;
}