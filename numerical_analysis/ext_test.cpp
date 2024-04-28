// main.cpp
#include <iostream>
#include <dlfcn.h>

typedef int (*ExternalFunction)(int, int);

int main() {
    std::string libraryPath;
    std::cout << "Enter path to the external library: ";
    std::cin >> libraryPath;

    // Load the external library
    void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // Get the function pointer
    ExternalFunction externalFunction = (ExternalFunction)dlsym(handle, "externalFunction");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'externalFunction': " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    // Call the function
    int result = externalFunction(5, 3);
    std::cout << "Result: " << result << std::endl;

    // Close the library
    dlclose(handle);
    return 0;
}
