#include<iostream>
#include <limits>
#include <iomanip>
#include "interval.h"

using namespace std;

int main(){
    long double xx;
    cin >> xx;
    Interval x;
    x.read_float(xx);
    return 0;
}