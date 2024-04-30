#include <iostream>
#include <cmath>

#include "interval.h"

using namespace std;

int main(){
    double a;
    cin >> a;
    Interval r;
    r.read_float(to_string(a));
    cout << "  " << to_string(sinf128(a), 35, 'e') << endl;
    cout << sin(r) << endl;


    return 0;
}  