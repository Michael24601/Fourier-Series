#include <node.h>
#include <iostream>
#include <sstream>
#include "BezierCurveVector.h"
#include <iomanip>

namespace fs {
    using v8:: FunctionCallbackInfo;
    using v8 :: Isolate;
    using v8 :: Local;
    using v8 :: Object;
    using v8 :: Number;
    using v8 :: Value;
    using v8 :: String;
    using v8::Exception;

     std::vector<std::string> split (const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss (s);
        std::string item;

        while (getline (ss, item, delim)) {
            result.push_back (item);
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

    std::string polynomialToString(const Polynomial& p){
        std::string s = "" + std::to_string(p.getCoefficient(0));
        for(int i = 1; i <= p.getDegree(); i++){
            if(p.getCoefficient(i) != 0){
                s += " + " + std::to_string(p.getCoefficient(i)) + "t^" 
                    + std::to_string(i);
            }
        }
        return s;
    }

    std::string bezierCurveToString(const BezierCurve& b){
        std::string s = "X(t) = " + polynomialToString(b.getX());
        s += "  Y(t) = " + polynomialToString(b.getY());
        return s;
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

            // n is the number of circles to be generated
    std::string generateCirclesOnly(real dt, int n, const BezierCurveVector& h){
        std::string s = "";
        ComplexNumber c = h.integrate(dt, 0);
        s += std::to_string(c.getReal()) + " " 
            + std::to_string(c.getImaginary()) + " ";
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
            s +=  std::to_string(c.getReal()) + " " 
                + std::to_string(c.getImaginary()) + " ";
        }
        return s;
    }
  
    // Exported function
    void generateFourrier(const FunctionCallbackInfo<Value>&args)
    {
        Isolate* isolate = args.GetIsolate();

        std::string s = "Hello";

        // Check the number of arguments passed.
        if (args.Length() != 3) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, 
                    "Wrong number of arguments").ToLocalChecked()));
            return;
        }
        // Check the argument types
        else if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, 
                    "Wrong argument datatype").ToLocalChecked()));
            return;
        }
        v8::String::Utf8Value str1(isolate, args[0]);
        std::string input(*str1);
        v8::String::Utf8Value str2(isolate, args[1]);
        std::string input2(*str2);
        v8::String::Utf8Value str3(isolate, args[2]);
        std::string input3(*str3);
        int circleNumber = std::stoi(input2);
        real dt = std::stod(input3);

        std::vector<std::vector<Point>> points = generateAllPoints(input);

        BezierCurveVector vector = generateBezierCurveVector(points);

        std::string output = generateCircles(dt, circleNumber, vector);

        args.GetReturnValue().Set(String::NewFromUtf8(
            isolate, output.c_str()).ToLocalChecked());
    }

     // Exported function
    void generateBezier(const FunctionCallbackInfo<Value>&args)
    {
        Isolate* isolate = args.GetIsolate();

        std::string s = "Hello";

        // Check the number of arguments passed.
        if (args.Length() != 1) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, 
                    "Wrong number of arguments").ToLocalChecked()));
            return;
        }
        // Check the argument types
        else if (!args[0]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, 
                    "Wrong argument datatype").ToLocalChecked()));
            return;
        }
        v8::String::Utf8Value str1(isolate, args[0]);
        std::string input(*str1);


        std::vector<std::vector<Point>> points = generateAllPoints(input);

        BezierCurveVector vector = generateBezierCurveVector(points);

        std::string output = "";

        for(int i = 0; i < vector.getBezierCurveNumber(); i++){
            output += "curve " + std::to_string(i + 1) 
                + " on [" + std::to_string(vector.getBezierCurve(i).getT0()) 
                + ", " + std::to_string(vector.getBezierCurve(i).getT1()) + "]: "; 
            output += bezierCurveToString(vector.getBezierCurve(i)) + "\n";
        }

        args.GetReturnValue().Set(String::NewFromUtf8(
            isolate, output.c_str()).ToLocalChecked());
    }

        // Exported function
    void generateVectors(const FunctionCallbackInfo<Value>&args)
    {
        Isolate* isolate = args.GetIsolate();

        std::string s = "Hello";

        // Check the number of arguments passed.
        if (args.Length() != 3) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, 
                    "Wrong number of arguments").ToLocalChecked()));
            return;
        }
        // Check the argument types
        else if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, 
                    "Wrong argument datatype").ToLocalChecked()));
            return;
        }
        v8::String::Utf8Value str1(isolate, args[0]);
        std::string input(*str1);
        v8::String::Utf8Value str2(isolate, args[1]);
        std::string input2(*str2);
        v8::String::Utf8Value str3(isolate, args[2]);
        std::string input3(*str3);
        int circleNumber = std::stoi(input2);
        real dt = std::stod(input3);

        std::vector<std::vector<Point>> points = generateAllPoints(input);

        BezierCurveVector vector = generateBezierCurveVector(points);

        std::string output = generateCirclesOnly(dt, circleNumber, vector);

        args.GetReturnValue().Set(String::NewFromUtf8(
            isolate, output.c_str()).ToLocalChecked());
    }
 
    // Exports the function
    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "generateFourrier", generateFourrier);
        NODE_SET_METHOD(exports, "generateBezier", generateBezier);
        NODE_SET_METHOD(exports, "generateVectors", generateVectors);
    }
  
    NODE_MODULE(NODE_GYP_MODULE_NAME,Initialize);
}
