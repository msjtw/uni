#include <iostream>
#include <dlfcn.h>

#include "interval.h"
#include "newton_raphson.h"

using namespace std;

template<typename T>
int read_fuct(string path, T (*f)(T), T (*df)(T), T (*d2f)(T)){
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }
    f = (T (*)(T))dlsym(handle, "f");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'externalFunction': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }
    df = (T (*)(T))dlsym(handle, "df");
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'externalFunction': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }
    d2f = (T (*)(T))dlsym(handle, "d2f");
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'externalFunction': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }
    return 0;
}

int main(){
    std::string libraryPath;
    std::cout << "Enter path to the external library: ";
    std::cin >> libraryPath;

    Interval (*f)(Interval);
    Interval (*df)(Interval);
    Interval (*d2f)(Interval);
    read_fuct<Interval>(libraryPath, f, df, d2f);

    Interval res, fatx;
    int it;
    int st = newton_raphson<Interval>(res,f, df, d2f ,1e6, Interval("1e-10"), fatx, it);

    cout << res;
    return 0;
}  