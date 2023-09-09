#include <cstdlib>
#include <iostream>

int main() {
    for (std::string digit; std::cin >> digit;) {
        char* end{};
        std::cout << strtol(digit.data(), &end, 16) << std::endl;
        ;
    }
    return 0;
}
