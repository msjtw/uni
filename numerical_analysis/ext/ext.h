// external_library.h
#ifndef EXT_H
#define EXT_H


#include "/home/msjtw/Documents/uni/numerical_analysis/interval.h"

// Function prototype
extern "C" {
    Interval f(Interval);
    Interval df(Interval);
    Interval d2f(Interval);

    _Float128 ff(_Float128);
    _Float128 dff(_Float128);
    _Float128 d2ff(_Float128);
}

#endif // EXTERNAL_LIBRARY_H
