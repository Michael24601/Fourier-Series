
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#include "unit.h"
#include "BezierCurveVector.h"


using namespace fs;


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

std::vector<Point>generatePoints(std::string& input){
        std::vector<Point> points;
        std::vector<std::string> numbers = split(input, ' ');
        points.resize(((double)numbers.size())/2);
        for(int i = 0; i < numbers.size(); i+=2){
            points[i/2] = Point(stod(numbers[i]), stod(numbers[i+1]));
        }
        return points;
}


std::vector<std::vector<Point>>generateAllPoints(std::string& input){
    std::vector<std::string> strings = split(input, ',');
    std::vector<std::vector<Point>> v;
    v.resize(strings.size());
    for(int i = 0; i < v.size(); i++){
        v[i] = generatePoints(strings[i]);
    }
    return v;
}


BezierCurveVector generateBezierCurveVector(std::vector<std::vector<Point>> points){
    /**********************************************************************
     * Interval set in such a way as to allow the animation to fully take 
     * place between 0 and 1 seconds.
    **********************************************************************/ 
    real interval = 1.0/points.size();
    BezierCurveVector vector(interval);
    for(auto i = 0; i < points.size(); i++){
        vector.addBezierCurve(points[i]);
    }
    return vector;
}


// n is the number of circles to be generated
std::string generateCircles(real dt, int n, const BezierCurve& h){
    std::string s = "";
    ComplexNumber c = h.integrate(dt, 0);
    s += "complex(" + std::to_string(c.getReal()) + ", " 
        + std::to_string(c.getImaginary()) + ")\n";
    for(int i = 1; i < n; i++){
        if(i % 2 == 1){
            /**************************************************************
             * Odd complex coefficients are c[1], c[2] ... which need 
             * -1 and -2 as n to cancel the vector's movement and get its 
             * value.
            **************************************************************/
            c = h.integrate(dt , -(i/2 + 1));
        }
        else if(i % 2 == 0){
            /**************************************************************
             * Even complex coefficients are c[-1], c[-2] ... which need 
             * 1 and 2 as n to cancel the vector's movement and get its 
             * value.
            **************************************************************/
            c = h.integrate(dt, i/2);
        }
        s += "complex(" + std::to_string(c.getReal()) + ", " 
            + std::to_string(c.getImaginary()) + ")\n";
    }
    return s;
}

// n is the number of circles to be generated
std::string generateCircles(real dt, int n, const BezierCurveVector& h){
    std::string s = "";
    ComplexNumber c = h.integrate(dt, 0);
    s += "complex (" + std::to_string(c.getReal()) + ", " 
        + std::to_string(c.getImaginary()) + ")\n,";
    for(int i = 1; i < n; i++){
        if(i % 2 == 1){
            /**************************************************************
             * Odd complex coefficients are c[1], c[2] ... which need 
             * -1 and -2 as n to cancel the vector's movement and get its 
             * value.
            **************************************************************/
            c = h.integrate(dt , -(i/2 + 1));
        }
        else if(i % 2 == 0){
            /**************************************************************
             * Even complex coefficients are c[-1], c[-2] ... which need 
             * 1 and 2 as n to cancel the vector's movement and get its 
             * value.
            **************************************************************/
            c = h.integrate(dt, i/2);
        }
        // s += "comple" + std::to_string((i%2 == 0 ? -(i/2) : (i/2 + 1))) + "] = (" 
            s  += "complex (" + std::to_string(c.getReal()) + ", " 
            + std::to_string(c.getImaginary()) + ")\n,";
    }
    return s;
}


// int main() {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(shape);
//         window.display();
//     }

//     return 0;
// }


#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

namespace fs{

    // Function to parse an SVG file and extract bezier curves
    std::string parseSVG(const std::string& filePath) {
        std::vector<std::vector<Point>> bezierCurves; // Vector to store bezier curves

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

    
    std::vector<std::vector<Point>> parseSVGPath(const std::string& pathData) {
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
                    // First point in Bezier curve is the last point in the last curve
                    points.push_back(temp);
                    pathStream >> x >> y;
                    // Get a new temp
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
                    // Line between last and first point
                    points.push_back(temp);
                    points.push_back(vectorOfPoints[0][0]);
                    vectorOfPoints.push_back(points);
                default:
                    break;
            }
        }

        return vectorOfPoints;
    }
}

int main() {
    std::string filePath = "svg/fourier.svg";
    std::string s = fs::parseSVG(filePath);

    std::vector<std::vector<fs::Point>> points = fs::parseSVGPath(s);
    // Print the vector of points
    for (const auto& curve : points) {
        for (const auto& point : curve) {
            std::cout << point;
        }
        std::cout << std::endl;
    }

    return 0;
}