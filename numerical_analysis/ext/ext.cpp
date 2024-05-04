// external_library.cpp
// to compile
// g++ -shared -o numerical_analysis/ext/libext.so numerical_analysis/interval.cpp numerical_analysis/ext/ext.cpp -fPIC


#include "ext.h"
#include "cmath"

typedef long double ld;

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

ld ff(ld x) {
    ld ret;
    ret = pow(x, 3);
    ret = ret + (6 * pow(x, 2));
    ret = ret + (10 * x);
    ret = ret + -3;
    return ret;
}

ld dff(ld x) {
    ld ret;
    ret = 3 * pow(x, 2);
    ret = ret + (12 * x);
    ret = ret + 10;
    return ret;
}

ld d2ff(ld x) {
    ld ret;
    ret = 6 * x;
    ret = ret + 12;
    return ret;
}
