#include "interval.h"
#include <limits>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <iostream>


bool Interval::read_string(std::string value){
    _Float128 fvalue = strtof128(value.c_str(), NULL);
    Interval::left = nextafterf128(fvalue, -INFINITY);
    Interval::right = nextafterf128(fvalue, INFINITY);

    

    std::cout << Interval::to_string(fvalue, 50) << std::endl;
    std::cout << Interval::to_string(Interval::left, 50) << std::endl << Interval::to_string(Interval::right, 50) << std::endl;
    std::cout << Interval::to_string(right-left, 4) << std::endl;
    return true;
}

bool Interval::read_interval(std::string left, std::string right){
    _Float128 f_left = strtof128(left.c_str(), NULL);
    _Float128 f_right = strtof128(right.c_str(), NULL);
    Interval::left = nextafterf128(f_left, -INFINITY);
    Interval::right = nextafterf128(f_right, INFINITY);
    return true;
}

std::string Interval::to_string( _Float128 fp, int len) {
    char buf[11000];
    std::string buf2;
    std::string format = "%." + std::to_string(5000) + "f";
    int sz = strfromf128(buf, sizeof buf, format.c_str(), fp);
    std::string ret(buf);
    return ret;
}

// std::ostream& operator<<(std::ostream& os, Interval& intrvl){
//     os << intrvl.to_string(intrvl.left) << std::endl << intrvl.to_string(intrvl.right);
//     return os;
// }
