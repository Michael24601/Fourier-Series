/******************************************************************************
 * unit.h
 * Author: Michael Saba
 * Date: 1/15/2023
 * Header file for the unit typedef, used to easily adjust precision
******************************************************************************/

#ifndef UNIT_H
#define UNIT_H

namespace fs {
    /**************************************************************************
     * Defines a numeric typedef to easily change precision.
     * Use double not float, as float is not precise enough for some small
     * angle nudges we need to rotate vectors in, and the inaccuracy builds
     * up. The Fourier series starts off accurate, but quickly becomes
     * chaotic.
    **************************************************************************/ 
    typedef double real;
    // Defines the mathematical constant PI
    constexpr real PI = 3.141592;
}

#endif