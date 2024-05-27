// external_library.cpp
// to compile
// g++ -shared -o numerical_analysis/ext/libext.so numerical_analysis/interval.cpp numerical_analysis/ext/ext.cpp -fPIC


#include "ext.h"
#include "cmath"

Interval f(Interval intrvl) {
    Interval ret;
    ret = 2 * pow(intrvl, 3);
    ret = ret + Interval("-3") * intrvl;
    ret = ret +  Interval("6");
    return ret;
}

Interval df(Interval intrvl) {
    Interval ret;
    ret = 6 * pow(intrvl, 2);
    ret = ret + (Interval("-3"));
    return ret;
}

Interval d2f(Interval intrvl) {
    Interval ret;
    ret = Interval("12") * intrvl;
    return ret;
}

_Float128 ff(_Float128 x) {
    _Float128 ret;
    ret = 2 * pow(x, 3);
    ret = ret + -3 * x;
    ret = ret +  6;
    return ret;
}

_Float128 dff(_Float128 x) {
    _Float128 ret;
    ret = 6 * pow(x, 2);
    ret = ret -3;
    return ret;
}

_Float128 d2ff(_Float128 x) {
    _Float128 ret;
    ret = 12 * x;
    return ret;
}
