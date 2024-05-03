// external_library.h
#ifndef EXT_H
#define EXT_H

// #ifdef __cplusplus
// extern "C" {
// #endif

#include "/home/msjtw/Documents/uni/numerical_analysis/interval.h"

// Function prototype
extern "C" {
    Interval f(Interval);

    Interval df(Interval);

    Interval d2f(Interval);
}

// #ifdef __cplusplus
// }
// #endif

#endif // EXTERNAL_LIBRARY_H
