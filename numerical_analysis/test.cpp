#include <iostream>

#include "interval.h"

using namespace std;


int main(){
    string s;
    cin >> s;
    Interval r;
    r.read_float(s);
    cout << r << endl;
    cout << sqrt(r) << endl;


    return 0;
}  