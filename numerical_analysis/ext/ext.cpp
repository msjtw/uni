// external_library.cpp
// to compile
// g++ -shared -o libext.so ext.cpp -fPIC


#include "ext.h"

int externalFunction(int a, int b) {
    return a - b;
}
