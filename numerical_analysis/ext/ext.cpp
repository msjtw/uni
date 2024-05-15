// external_library.cpp
// to compile
// g++ -shared -o numerical_analysis/ext/libext.so numerical_analysis/interval.cpp numerical_analysis/ext/ext.cpp -fPIC


#include "ext.h"
#include "cmath"

Interval f(Interval intrvl) {
    Interval ret;
    ret = pow(intrvl, 4);
    ret = ret + (Interval("-5") * pow(intrvl, 2));
    ret = ret +  Interval("4");
    return ret;
}

Interval df(Interval intrvl) {
    Interval ret;
    ret = Interval("4") * pow(intrvl, 3);
    ret = ret + (Interval("-10") * intrvl);
    return ret;
}

Interval d2f(Interval intrvl) {
    Interval ret;
    ret = Interval("12") * pow(intrvl, 2);
    ret = ret +  Interval("-10");
    return ret;
}

_Float128 ff(_Float128 x) {
    _Float128 ret;
    ret = pow(x, 4); 
    ret = ret + (-5 * pow(x, 2));
    ret = ret + 4;
    return ret;
}

_Float128 dff(_Float128 x) {
    _Float128 ret;
    ret = 4 * pow(x, 3);
    ret = ret + (-10 * x);
    return ret;
}

_Float128 d2ff(_Float128 x) {
    _Float128 ret;
    ret = 12 * pow(x, 2);
    ret = ret + -10;
    return ret;
}
