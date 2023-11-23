
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "unit.h"
#include "FourierSeries.h"


int main() {

    std::string filePath = "svg/giga.svg";
    // A low number of circles makes it lose its shape and become blob-like,
    // (the number of rotating vectors, the tip of which traces the image)
    int numberOfCircles = 500;
    // A low integration accuracy makes the drawing spikier
    fs::real integrationInterval = 0.0001;
    int canvasSize = 800; // In px
    int frameRate = 60;
    // A low animation time means there won't be enough frames to smoothly
    // animate the drawing, which makes it blocky
    int animationTime = 20000; // In ms
    bool showCircles = true;

    /**************************************************************************
     * Since we set the Bezier Curve to start and finish at 0 and 1 seconds
     * (1000 milliseconds), and since the animation is running at some frames
     * per second, we need to determine how much to rotate the circles by
     * each frame, knowing the angle offset must start at 0 and end at
     * 2 * PI.
     * The formula is (2 PI) / (number of frames)
     * where numbere of frames = (1000 / frameRate) * (animationTime / 1000)
    **************************************************************************/
    fs::real angleOffset = (2 * fs::PI) / (animationTime / (1000 / frameRate));
    

    fs::FourierSeries fourierSeries;
    
    // The svg path
    std::string path = fourierSeries.parseSVG(filePath);
    std:: cout << path << "\n\n"; 

    // The points in each bezier curve, parsed from the path
    std::vector<std::vector<fs::Point>> points = 
        fourierSeries.parseSVGPath(path);
    for (const auto& curve : points) {
        for (const auto& point : curve) {
            std::cout << point << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";

    // Now the points needs to be translated and scaled so they're in the
    // middle of the canvas and fit well.
    fourierSeries.movePointsToMinimizeDistance(points);
    fourierSeries.scalePoints(points, canvasSize);

    // The bezier curves in their parametric forms, where the ith curve starts
    // at t = i and ends at t = i+1 starting with curve 0, and ending with
    // the curve that connects back to it.
    fs::BezierCurveVector bezierCurveVector = 
        fourierSeries.generateBezierCurveVector(points);
    std::cout << bezierCurveVector << "\n\n";
    
    // The complex numbers generated in order to draw the image path using 
    // a fourier series (with n circles).
    std::vector<fs::ComplexNumber> circles = fourierSeries.generateCircles(
        integrationInterval,
        numberOfCircles,
        bezierCurveVector
    );
    for (int i = 0; i < circles.size(); i++) {
        std::cout << "Vector [" << i << "]: " << circles[i] << "\n";
    }
    std::cout << "\n\n";


    // This part shows the Fourier Series drawing the image

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // Adjust the level as needed
    sf::RenderWindow window(sf::VideoMode(canvasSize, canvasSize), 
        "Fourier Series", sf::Style::Default, settings);

    // Centeres the view at the origin (0, 0)
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(canvasSize, canvasSize));
    window.setView(view);

    sf::VertexArray imageShape(sf::LineStrip);
    // Total angle rotated, used to determine how many loops we've done
    fs::real totalAngle = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        // Draws the vectors drawing the image
        sf::VertexArray vectors(sf::LineStrip);
        vectors.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::Blue));
        // Draws the circles in which the vectors rotate
        std::vector<sf::CircleShape> circleShapes;

        fs::ComplexNumber tip;
        for(int i = 0; i < circles.size(); i++){

            sf::CircleShape circleShape;
            circleShape.setRadius(circles[i].getMagnitude());
            circleShape.setPosition(tip.getReal(), tip.getImaginary());
            circleShape.setOrigin(circleShape.getRadius(),
                circleShape.getRadius());
            circleShape.setOutlineThickness(1);
            circleShape.setFillColor(sf::Color::Transparent);
            sf::Color outlineColor = sf::Color(255, 255, 255);
            outlineColor.a = 80;  // Opacity
            circleShape.setOutlineColor(outlineColor);
            circleShapes.push_back(circleShape);

            // The first circle does not rotate
            if(i == 0){
                tip += circles[i];
            }
            else {
                if(i % 2 == 1){
                    circles[i].addAngle(angleOffset * ((i+1)/2));
                } else {
                    circles[i].addAngle(angleOffset * -(i/2));
                }
                tip += circles[i];
            }
            vectors.append(sf::Vertex(sf::Vector2f(tip.getReal(), 
                tip.getImaginary()), sf::Color::Blue));
        }

        imageShape.append(sf::Vertex(sf::Vector2f(tip.getReal(), 
            tip.getImaginary()), sf::Color::Red));

        totalAngle += angleOffset;

        window.setFramerateLimit(frameRate);
        window.clear();
        // Only draws the fourier series the first loop, then just displays
        // the drawn image alone (since a fourier series is periodic).
        if(totalAngle < 2 * fs::PI){
            if(showCircles){
                for(int i = 0; i < numberOfCircles; i++){
                    window.draw(circleShapes[i]);
                }
            }
            window.draw(vectors);
        }
        window.draw(imageShape);
        window.display();
    }

    return 0;
}