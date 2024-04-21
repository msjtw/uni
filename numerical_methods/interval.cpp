#include "interval.h"
#include <limits>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

bool Interval::read_float(long double value){
    Interval::left = Interval::lower_machine(value);
    Interval::right = Interval::upper_machine(value);
    std::cout << std::setprecision(std::numeric_limits<decltype(value)>::digits10) << left << std::endl << right << std::endl;
    return true;
}

bool Interval::read_interval(long double left, long double right){
    Interval::left = Interval::lower_machine(left);
    Interval::right = Interval::upper_machine(right);
    //std::cout << left << std::endl << right << std::endl;
    return true;
}

long double Interval::upper_machine(long double value){
    std::string s_value = Interval::to_string(value);
    cout << "a: " << fixed << std::setprecision(std::numeric_limits<decltype(value)>::digits10) << s_value << "    " << value << endl;
    cout << "a2: " << fixed << std::setprecision(std::numeric_limits<decltype(value)>::digits10) << stold(Interval::string_add(s_value, 1)) << "    " << value << endl;
    while(stold(Interval::string_add(s_value, 1)) == value){
        s_value = Interval::string_add(s_value, 1);
        std::cout << "next: " << fixed << std::setprecision(std::numeric_limits<decltype(value)>::digits10) << stold(s_value) << std::endl;
    }
    cout << "a: " << fixed << std::setprecision(std::numeric_limits<decltype(value)>::digits10) << s_value << endl;
    return stold(s_value);
}

long double Interval::lower_machine(long double value){
    std::string s_value = Interval::to_string(value);
    cout << fixed << std::setprecision(std::numeric_limits<decltype(value)>::digits10) << s_value << endl;
    while(stold(Interval::string_add(s_value, -1)) == value){
        s_value = Interval::string_add(s_value, -1);
    }
    cout << fixed << std::setprecision(std::numeric_limits<decltype(value)>::digits10) << s_value << endl;
    return stold(s_value);
}

std::string Interval::string_add(std::string s_value, int n){
    if(n == 1){
        s_value[s_value.size()-1] += 1;
        int i = s_value.size()-1;
        while(s_value[i] > '9' and i > 0){
            s_value[i] -= 10;
            i--;
            s_value[i] += 1;
        }
    }
    else if(n == -1){
        s_value[s_value.size()-1] -= 1;
        int i = s_value.size()-1;
        while(s_value[i] < '0' and i > 0){
            s_value[i] += 10;
            i--;
            s_value[i] -= 1;
        }
    }
    //cout << "addddd   " << s_value << endl;
    return s_value;
}

std::string Interval::to_string(long double value){
    auto digits10 = std::numeric_limits<decltype(value)>::digits10;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(digits10) << value;
    return stream.str();
}
