#pragma once
#include "math/polynomial.h" // We operate on our Polynomial class
#include "scheme/params.h" // We need the Parameters class for NTT

// The NTT functions are pure utility functions, so we can place them
// in a namespace instead of a class.
namespace NTT {

    // The forward NTT converts a polynomial from its standard coefficient form
    // into a "point-value" representation, which is easy to multiply.
    void forward(Polynomial& p, const Parameters& params);


    // The inverse NTT converts from the "point-value" representation
    // back to the standard coefficient form.
   void inverse(Polynomial& p, const Parameters& params);
}