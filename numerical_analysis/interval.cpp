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
#include <climits>


using std::string;

Interval::Interval(){
    left = 0;
    right = 0;
}

Interval::Interval(std::string value){
    read_float(value);
}

Interval::Interval(_Float128 _left, _Float128 _right){
    left = _left;
    right = _right;
}

bool Interval::read_float(std::string value){
    value = sci_to_full(value);
    bool neg = false;
    if(value[0] == '-'){
        neg = true;
    }
    _Float128 fvalue = strtof128(value.c_str(), NULL);
    int cmp_res =  cmp(value, to_string(fvalue, 5000, 'f'));
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
    _left = sci_to_full(_left);
    _right = sci_to_full(_right);
    bool neg = false;
    if(_left[0] == '-'){
        neg = true;
    }
    _Float128 f_left = strtof128(_left.c_str(), NULL);
    int cmp_res = cmp(_left, to_string(f_left, 5000, 'f'));
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
    cmp_res = cmp(_right, to_string(f_right, 5000, 'f'));
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
    for(int i = 0 ; i < (int)a.size(); i++){
        if(b[i] > a[i]){
            return 2;
        }
        if(a[i] > b[i]){
            return 0;
        }
    }
    return 1;
}

std::string sci_to_full(std::string sci) {
    if(sci.find('E') != string::npos){
        sci[sci.find('E')] = 'e';
    }
    if(sci.find(',') != string::npos){
        sci[sci.find(',')] = '.';
    }
    int p = sci.find('e');
    if(p == (int)string::npos)
        return sci;
    string num = sci.substr(0, p);
    int pow = std::stoi(sci.substr(p+1));
    if(num.find('.') == string::npos)
        num += ".";
    if(pow > 0){
        for(int i = 0; i < pow; i++)
            num += "0";
        p = num.find('.');
        for(int i = 0; i < pow; i++){
            std::swap(num[p+i],num[p+i+1]);
        }
    }
    else{
        pow *= -1;
        for(int i = 0; i < pow; i++)
            num = "0" + num;
        p = num.find('.');
        for(int i = 0; i < pow; i++){
            std::swap(num[p-i],num[p-i-1]);
        }
    }
    return num;
}

_Float128 Interval::width(){
    return right-left;
}

Interval Interval::operator +(const Interval & intrvl) const{
    Interval ret;
    std::fesetround(FE_DOWNWARD);
    ret.left = left + intrvl.left;
    std::fesetround(FE_UPWARD);
    ret.right = right + intrvl.right;
    std::fesetround(FE_TONEAREST);
    return ret;
}

Interval Interval::operator -(const Interval & intrvl) const{
    Interval ret;
    std::fesetround(FE_DOWNWARD);
    ret.left = left - intrvl.right;
    std::fesetround(FE_UPWARD);
    ret.right = right - intrvl.left;
    std::fesetround(FE_TONEAREST);
    return ret;
}

Interval Interval::operator *(const Interval & intrvl) const{
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

Interval Interval::operator /(const Interval & intrvl) const{
    if(intrvl.left <= 0 and intrvl.right >= 0)
        throw std::runtime_error("Division by an interval containing 0." + to_string(intrvl));
    _Float128 _left, _right;
    std::fesetround(FE_DOWNWARD);
    _left = 1/intrvl.right;
    std::fesetround(FE_UPWARD);
    _right = 1/intrvl.left;
    std::fesetround(FE_TONEAREST);
    Interval ret(_left, _right);
    return Interval(this->left, this->right)*ret; 
}

bool Interval::operator ==(const Interval & intrvl) const{
    if(left != intrvl.left)
        return false;
    if(right != intrvl.right){
        return false;
    }
    return true;
}

std::string to_string(const _Float128 fp, const int n, const char type){
    char buf[11000];
    std::string buf2;
    std::string format = "%." + std::to_string(n) + type;
    strfromf128(buf, sizeof buf, format.c_str(), fp);
    std::string ret(buf);
    return ret;
}

std::string to_string(const Interval intrvl, const int n, const char type){
    std::string ret = + "[ " + to_string(intrvl.left, n, type) + ", " + to_string(intrvl.right) + " ]\n" + to_string(intrvl.right-intrvl.left);
    return ret;
}

std::ostream& operator<<(std::ostream& os, const Interval& intrvl){
    os << to_string(intrvl);
    return os;
}

Interval abs(const Interval &intrvl){
    Interval ret;
    if(intrvl.left <= 0 and intrvl.right >= 0){
        ret.left = 0;
    }
    else{
        _Float128 a = intrvl.left;
        _Float128 b = intrvl.left;
        a *= (a < 0 ? -1 : 1);
        b *= (b < 0 ? -1 : 1);
        if(a < b){
            ret.right = a;
        }
        else{
            ret.right = b;
        }
    }
    _Float128 a = intrvl.right;
    _Float128 b = intrvl.right;
    a *= (a < 0 ? -1 : 1);
    b *= (b < 0 ? -1 : 1);
    if(a > b){
        ret.left = a;
    }
    else{
        ret.left = b;
    }
    return ret;
}

bool neg(const Interval &intrvl){
    return (intrvl.left <= 0 or intrvl.right <= 0);
}

bool con_zero(const Interval &intrvl){
    return (intrvl.left <= 0 and  intrvl.right >= 0);
}

Interval make_intr(const Interval &a, const Interval &b){
    Interval res;
    if(a.right > b.right)
        res.right = a.right;
    else
        res.right = b.right;

    if(a.left < b.left)
        res.left = a.left;
    else
        res.left = b.left;

    return res;
}

Interval sqrt(const Interval &intrvl){
    if(intrvl.left < 0 or intrvl.right < 0)
        throw std::runtime_error("Square root of negative number.");
    Interval ret;
    ret.left = sqrtf128(intrvl.left, false);
    ret.right = sqrtf128(intrvl.right, true);
    return ret;
}

Interval pow(const Interval &intrvl, int _pow){
    if(_pow == 0)
        return Interval("1");
    if(_pow & 1){
        return pow(intrvl, _pow-1) * intrvl;
    }
    else{
        Interval ret = abs(pow(intrvl, _pow >> 1));
        ret = ret*ret;
        return ret;
    } 
}

_Float128 pow(const _Float128 x, int _pow){
    if(_pow == 0)
        return 1;
    if(_pow & 1){
        return pow(x, _pow-1) * x;
    }
    else{
        _Float128 ret = pow(x, _pow >> 1);
        return ret*ret;
    } 
}

_Float128 sqrtf128(const _Float128 intrvl, const bool top){
    _Float128 a = 0;
    _Float128 b = intrvl;
    _Float128 width = b-a;
    _Float128 eps = 1e-30;
    int iter = 1e6;
    while(width > eps and iter --> 0){
        _Float128 m = (a+b)/2;
        if(m*m > intrvl){
            b = m;
        }
        else{
            a = m;
        }
    }
    if(top)
        return b;
    else
        return a;
};

Interval sin(Interval intrvl){
    Interval ret;
    ret.left = nextafterf128(sinf128(intrvl.left), -INFINITY);
    ret.right = nextafterf128(sinf128(intrvl.right), INFINITY);

    return ret;
}

Interval cos(Interval intrvl){
    Interval ret;
    ret.left = nextafterf128(cosf128(intrvl.left), -INFINITY);
    ret.right = nextafterf128(cosf128(intrvl.right), INFINITY);

    return ret;
}