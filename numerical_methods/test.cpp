#include <iostream>
#include <stdfloat>
#include <limits>
#include <iomanip>
#include <cmath>

#include "interval.h"

using namespace std;

int main(){
    string a;
    cin >> a;
    Interval x;
    x.read_string(a);
    return 0;
}