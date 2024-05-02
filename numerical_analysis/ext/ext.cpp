// external_library.cpp
// to compile
// g++ -shared -o libext.so ext.cpp -fPIC


#include "ext.h"

Interval f(Interval intrvl) {
    Interval ret;
    ret = ret + ((pow(intrvl) * intrvl));
    ret = ret + (Interval("6") * pow(intrvl));
    ret = ret + (Interval("10") * intrvl);
    ret = ret +  Interval("-3");
    return ret;
}

Interval df(Interval intrvl) {
    Interval ret;
    ret = ret + (Interval("3") * pow(intrvl));
    ret = ret + (Interval("12") * intrvl);
    ret = ret +  Interval("10");
    return ret;
}

Interval d2f(Interval intrvl) {
    Interval ret;
    ret = ret + (Interval("6") * intrvl);
    ret = ret +  Interval("12");
    return ret;
}