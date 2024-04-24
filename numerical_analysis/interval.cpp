// msjtw 2024
// https://github.com/msjtw

#include "interval.h"
#include <limits>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cfenv>


using std::string;

Interval::Interval(){
    left = 0;
    right = 0;
}

Interval::Interval(_Float128 _left, _Float128 _right){
    left = _left;
    right = _right;
}

bool Interval::read_string(std::string value){
    bool neg = false;
    if(value[0] == '-'){
        neg = true;
    }
    _Float128 fvalue = strtof128(value.c_str(), NULL);
    int cmp_res =  cmp(value, Interval::to_string(fvalue));
    //std::cout << cmp_res << std::endl;
    //std::cout << to_string(fvalue) << std::endl;
    if(cmp_res == 1){
        // value == fvalue
        left = fvalue;
        right = fvalue;
    }
    else if((cmp_res == 0 and !neg) or (cmp_res == 2 and neg)){
        // value > fvalue
        left = fvalue;
        right = nextafterf128(fvalue, INFINITY);
    }
    else{
        // value < fvalue
        left = nextafterf128(fvalue, -INFINITY);
        right = fvalue;
    }
    return true;
}

bool Interval::read_interval(std::string _left, std::string _right){
    bool neg = false;
    if(_left[0] == '-'){
        neg = true;
    }
    _Float128 f_left = strtof128(_left.c_str(), NULL);
    int cmp_res = cmp(_left, Interval::to_string(f_left));
    if((cmp_res <= 1 and !neg) or (cmp_res >= 1 and neg)){
        // _left >= f_left
        left = f_left;
    }
    else{
        // _left < f_left
        left = nextafterf128(f_left, -INFINITY);
    }

    neg = false;
    if(_right[0] == '-'){
        neg = true;
    }
    _Float128 f_right = strtof128(_right.c_str(), NULL);
    cmp_res = cmp(_right, Interval::to_string(f_right));
    if((cmp_res >= 1 and !neg) or (cmp_res <= 1 and neg)){
        // _right <= f_right
        right = f_right;
    }
    else{
        // _right > f_right
        right = nextafterf128(f_right, INFINITY);
    }
    return true;
}

int Interval::cmp(string a, string b){
    // return 0:
    //     a > b
    // return 1:
    //     a == b
    // return 2:
    //     a < b

    if(a.find('.') == string::npos)
        a += '.';
    if(b.find('.') == string::npos)
        b += '.';

    int p = a.length()-a.find('.')-1;
    while(p < 5000){
        a += '0';
        p++;
    }
    p = b.length()-b.find('.')-1;
    while(p < 5000){
        b += '0';
        p++;
    }
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    while(a.length() < 10000){
        a += '0';
    }
    while(b.length() < 10000){
        b += '0';
    }
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    //std::cout << a << std::endl << b << std::endl;
    for(int i = 0 ; i < a.size(); i++){
        if(b[i] > a[i]){
            return 2;
        }
        if(a[i] > b[i]){
            return 0;
        }
    }
    return 1;
}

Interval Interval::operator +(const Interval & intrvl) {
    Interval ret;
    std::fesetround(FE_DOWNWARD);
    ret.left = left + intrvl.left;
    std::fesetround(FE_UPWARD);
    ret.right = right + intrvl.right;
    std::fesetround(FE_TONEAREST);
    return ret;
}

Interval Interval::operator -(const Interval & intrvl) {
    Interval ret;
    std::fesetround(FE_DOWNWARD);
    ret.left = left - intrvl.left;
    std::fesetround(FE_UPWARD);
    ret.right = right - intrvl.right;
    std::fesetround(FE_TONEAREST);
    return ret;
}

Interval Interval::operator *(const Interval & intrvl) {
    Interval ret;
    _Float128 a,b,c,d;
    std::fesetround(FE_DOWNWARD);
    a = left*intrvl.left;
    b = left*intrvl.right;
    c = right*intrvl.left;
    d = right*intrvl.right;
    ret.left = std::min(std::min(std::min(a,b),c),d);
    std::fesetround(FE_UPWARD);
    a = left*intrvl.left;
    b = left*intrvl.right;
    c = right*intrvl.left;
    d = right*intrvl.right;
    ret.right = std::max(std::max(std::max(a,b),c),d);
    std::fesetround(FE_TONEAREST);
    return ret;
}

Interval Interval::operator /(const Interval & intrvl) {
    if(intrvl.left <= 0 and intrvl.right >= 0)
        throw std::runtime_error("Division by an interval containing 0.");
    _Float128 _left, _right;
    std::fesetround(FE_DOWNWARD);
    _left = 1/intrvl.right;
    std::fesetround(FE_UPWARD);
    _right = 1/intrvl.left;
    Interval ret(_left, _right);
    std::cout << ret << std::endl;
    return Interval(this->left, this->right)*ret; 
}

std::string Interval::to_string(_Float128 fp, int n, char type) {
    char buf[11000];
    std::string buf2;
    std::string format = "%." + std::to_string(n) + type;
    int sz = strfromf128(buf, sizeof buf, format.c_str(), fp);
    std::string ret(buf);
    return ret;
}

std::ostream& operator<<(std::ostream& os, Interval& intrvl){
    os << "[ " << intrvl.to_string(intrvl.left,50,'e') << ", " << intrvl.to_string(intrvl.right, 50,'e') << " ]" << std::endl << intrvl.to_string(intrvl.right-intrvl.left, 50,'e');
    return os;
}
