#include <iostream>
#include <dlfcn.h>

#include "interval.h"
#include "newton_raphson.h"

using namespace std;

//load f, df and d2f functions
template<typename T>
int read_fuct(string path, T (*&f)(T), T (*&df)(T), T (*&d2f)(T)){
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    string name;
    string suf = "";
    if (std::is_same<T, _Float128>::value){
        suf = "f";
    }
    
    name = "f" + suf;
    f = (T (*)(T))dlsym(handle, name.c_str());
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'f': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }

    name = "df" + suf;
    df = (T (*)(T))dlsym(handle, name.c_str());
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'df': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }

    name = "d2f" + suf;
    d2f = (T (*)(T))dlsym(handle, name.c_str());
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'd2f': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }
    return 0;
}

int main(){
    std::string libraryPath;
    libraryPath = "/home/msjtw/Documents/uni/numerical_analysis/ext2/libext.so";
    //std::cout << "Enter path to the external library: ";
    //std::cin >> libraryPath;

    Interval (*f)(Interval);
    Interval (*df)(Interval);
    Interval (*d2f)(Interval);
    read_fuct<Interval>(libraryPath, f, df, d2f);

    _Float128 (*ff)(_Float128);
    _Float128 (*dff)(_Float128);
    _Float128 (*d2ff)(_Float128);
    read_fuct<_Float128>(libraryPath, ff, dff, d2ff);

    // Interval one;
    // one.read_float("1");
    // cout << one << endl;
    // cout << f(one) << endl << df(one) << endl << d2f(one);

    // _Float128 xf = strtof128("-0.5", NULL), ffatx;
    // //_Float128 fatx;
    // int it;
    // int st;
    // st = newton_raphson_f(xf,ff, dff, d2ff ,10, 1e-16, ffatx, it);

    // //cout << to_string(ff(-2)) << endl;

    // cout << to_string(xf) << endl;
    // cout << to_string(ffatx) << endl;
    // cout << st << endl;
    // cout << it << endl << endl;

    // Interval res("-0.5"), fatx;
    // //_Float128 res = -1, fatx;
    // st = newton_raphson_i(res,f, df, d2f ,5, 1e-16, fatx, it);

    //cout << f(Interval("-2.2")) << endl;

    // cout << "x:  " << to_string(res) << endl;
    // cout << "fx: " << to_string(fatx) << endl;
    // cout << "it: " << it << endl;
    // cout << st << endl;
    // Interval a("2.2"), b("-1.5");

    // cout << a*b << endl;
    // cout << pow(res, 4);

    string s;
    while(cin >> s){
        Interval intr;
        intr.read_float(s);
        cout << sin(intr) << endl << cos(intr);
    }

    return 0;
}  
