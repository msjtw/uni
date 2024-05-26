// external_library.cpp
// to compile
// g++ -shared -o numerical_analysis/ext3/libext.so numerical_analysis/interval.cpp numerical_analysis/ext3/ext.cpp -fPIC


#include "ext.h"
#include "cmath"

Interval f(Interval x) {
    Interval ret;
    ret = pow(sin(x), 4); 
    ret = ret + 0.5L*sin(x);
    ret = ret - 0.5;
    return ret;
}

Interval df(Interval x) {
    Interval ret;
    ret = sin(2*x);
    ret = ret + 0.5L*cos(x);
    return ret;
}

Interval d2f(Interval x) {
    Interval ret;
    ret = 2 * cos(2*x);
    ret = ret - 0.5L*sin(x);
    return ret;
}

_Float128 ff(_Float128 x) {
    _Float128 ret;
    ret = pow(sinf128(x), 2); 
    ret = ret + 0.5L*sinf128(x);
    ret = ret - 0.5;
    return ret;
}

_Float128 dff(_Float128 x) {
    _Float128 ret;
    ret = sinf128(2*x);
    ret = ret + 0.5L*cosf128(x);
    return ret;
}

_Float128 d2ff(_Float128 x) {
    _Float128 ret;
    ret = 2 * cosf128(2*x);
    ret = ret - 0.5L*sinf128(x);
    return ret;
}
