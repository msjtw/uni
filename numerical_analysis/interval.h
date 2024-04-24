// msjtw 2024
// https://github.com/msjtw

#ifndef INTERVAL_H_
#define INTERVAL_H_

#include<string>
#include <iostream>

class Interval{
    public:
        Interval();
        Interval(_Float128, _Float128);
        bool read_string(std::string);
        bool read_interval(std::string, std::string);
        std::string to_string(_Float128, int n = 5000, char type = 'f');
        friend std::ostream& operator<<(std::ostream& os, Interval& intrvl);
        Interval operator+(const Interval & intrvl);
        Interval operator-(const Interval & intrvl);
        Interval operator*(const Interval & intrvl);
        Interval operator/(const Interval & intrvl);

    private:
        _Float128 left;
        _Float128 right;
        int cmp(std::string, std::string);

};

#endif /* INTERVAL_H_ */