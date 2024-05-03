// main.cpp
#include <iostream>
#include "my_library.h"
#include <dlfcn.h>

int main() {
    void* handle = dlopen("./libmy_library.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    using CreateMyLibraryInstanceFunc = MyLibrary* (*)();
    using DestroyMyLibraryInstanceFunc = void (*)(MyLibrary*);

    CreateMyLibraryInstanceFunc createInstance = reinterpret_cast<CreateMyLibraryInstanceFunc>(
        dlsym(handle, "createMyLibraryInstance"));
    DestroyMyLibraryInstanceFunc destroyInstance = reinterpret_cast<DestroyMyLibraryInstanceFunc>(
        dlsym(handle, "destroyMyLibraryInstance"));

    if (!createInstance || !destroyInstance) {
        std::cerr << "Cannot load factory functions\n";
        dlclose(handle);
        return 1;
    }

    MyLibrary* myLibrary = createInstance();
    if (!myLibrary) {
        std::cerr << "Failed to create instance\n";
        dlclose(handle);
        return 1;
    }

    int result = myLibrary->add(5, 3);
    std::cout << "Result: " << result << std::endl;

    destroyInstance(myLibrary);
    dlclose(handle);
    return 0;
}