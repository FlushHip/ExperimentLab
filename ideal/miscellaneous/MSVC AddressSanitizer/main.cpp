#include <iostream>

int g_array[100];

int main() {
    g_array[100] = 1;
    std::cout << "MSVC AddressSanitizer" << std::endl;
    return 0;
}
