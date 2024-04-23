#ifndef INTERVAL_H_
#define INTERVAL_H_

#include<string>
#include <limits>
#include <iostream>

class Interval{
    public:
        bool read_string(std::string);
        bool read_interval(std::string, std::string);
        std::string to_string(_Float128, int);
        friend std::ostream& operator<<(std::ostream& os, Interval& intrvl);
        _Float128 left;
        _Float128 right;

    private:
        const int precision = std::numeric_limits<_Float128>::digits10;

};

#endif //INTERVAL_H_