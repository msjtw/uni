#ifndef INTERVAL_H_
#define INTERVAL_H_

#include<string>

class Interval{
    public:
        bool read_float(long double);
        bool read_interval(long double, long double);
    private:
        long double left;
        long double right;

        long double upper_machine(long double);
        long double lower_machine(long double);

        std::string to_string(long double);

        std::string string_add(std::string, int);
};

#endif //INTERVAL_H_