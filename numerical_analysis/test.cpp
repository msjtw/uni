#include <iostream>
#include <dlfcn.h>

#include "interval.h"
#include "newton_raphson.h"

using namespace std;

//load f, df and d2f functions
template<typename T>
int read_fuct(string path, T (*&f)(T), T (*&df)(T), T (*&d2f)(T)){
    string suf = "f";
    if(typeid(T) == typeid(Interval))
        suf = "";
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    string name = "f"+suf;
    f = (T (*)(T))dlsym(handle, name.c_str());
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol '" << suf << "f': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }

    name = "df"+suf;
    df = (T (*)(T))dlsym(handle, name.c_str());
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol '" << suf << "df': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }

    name = "f"+suf;
    d2f = (T (*)(T))dlsym(handle, name.c_str());
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol '" << suf << "d2f': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }
    return 0;
}

int main(){
    std::string libraryPath;
    libraryPath = "/home/msjtw/Documents/uni/numerical_analysis/ext/libext.so";
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

    Interval res("-2.2"), fatx;
    int it;
    int st = newton_raphson<Interval>(res,f, df, d2f ,10, 1e-16, fatx, it);

    cout << res << endl;
    cout << st << endl;
    cout << it;
    return 0;
}  