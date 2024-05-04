// external_library.h
#ifndef EXT_H
#define EXT_H

typedef long double ld;

#include "/home/msjtw/Documents/uni/numerical_analysis/interval.h"

// Function prototype
extern "C" {
    Interval f(Interval);
    Interval df(Interval);
    Interval d2f(Interval);

    ld ff(ld);
    ld dff(ld);
    ld d2ff(ld);
}

#endif // EXTERNAL_LIBRARY_H
