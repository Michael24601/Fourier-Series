# Binding file for addon
# First run node-gyp configure, then node-gyp build
# Target name is the name that will be used by node as a module
# sources is the name of the main.cpp file, along with other source files
# include_dirs is for custome libraries (header files)
{
    "targets": [
        {
            "target_name": "addon",
            "sources": [ 
                "CPPSource/generateFourrier.cpp", 
                "CPPSource/Point.cpp", 
                "CPPSource/Polynomial.cpp", 
                "CPPSource/BezierCurve.cpp", 
                "CPPSource/BezierCurveVector.cpp",
                "CPPSource/ComplexNumber.cpp" 
            ],
            'include_dirs': [
                "CPPSource/Point.h",
                "CPPSource/ComplexNumber.h",
                "CPPSource/Polynomial.h",
                "CPPSource/BezierCurve.h",
                "CPPSource/BezierCurveVector.h",
                "CPPSource/constants.h",
                "CPPSource/unit.h",
            ]
        }
    ],
    
}