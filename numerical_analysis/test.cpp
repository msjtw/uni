#include <iostream>
#include <stdfloat>
#include <limits>
#include <iomanip>
#include <cmath>

#include "interval.h"

using namespace std;

int main(){
    string a, b;
    cin >> a >> b;
    Interval x, y;
    x.read_string(a);
    y.read_string(b);
    
    Interval z = x/y;

    cout << z << endl;

    cin >> a;
    x.read_string(a);
    cout << x;

    return 0;
}